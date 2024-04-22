/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OCEANBASE_STORAGE_OB_I_TABLET_MEMTABLE_H_
#define OCEANBASE_STORAGE_OB_I_TABLET_MEMTABLE_H_

#include "lib/utility/ob_print_utils.h"

#include "storage/ob_i_memtable_mgr.h"
#include "storage/memtable/ob_memtable_interface.h"
#include "storage/checkpoint/ob_freeze_checkpoint.h"

namespace oceanbase {
namespace storage {

class ObTabletMemtableMgr;

/*
 * Attention! When tx is rollback, insert/update/delete row count and size will not reduced accordingly
 */
struct ObMtStat {
  ObMtStat() { reset(); }
  ~ObMtStat() = default;
  void reset() { memset(this, 0, sizeof(*this)); }
  TO_STRING_KV(K_(insert_row_count),
               K_(update_row_count),
               K_(delete_row_count),
               K_(empty_mvcc_row_count),
               K_(frozen_time),
               K_(ready_for_flush_time),
               K_(create_flush_dag_time),
               K_(release_time),
               K_(last_print_time),
               K_(row_size));
  int64_t insert_row_count_;
  int64_t update_row_count_;
  int64_t delete_row_count_;
  int64_t empty_mvcc_row_count_;
  int64_t frozen_time_;
  int64_t ready_for_flush_time_;
  int64_t create_flush_dag_time_;
  int64_t release_time_;
  int64_t push_table_into_gc_queue_time_;
  int64_t last_print_time_;
  int64_t row_size_;
};

class ObMemtableState {
public:
  static const int64_t INVALID = -1;
  static const int64_t ACTIVE = 0;
  static const int64_t MAJOR_FROZEN = 1;
  static const int64_t MINOR_FROZEN = 2;
  static const int64_t MAJOR_MERGING = 3;
  static const int64_t MINOR_MERGING = 4;

public:
  bool is_valid(const int64_t state) { return state >= ACTIVE && state <= MINOR_MERGING; }
};

enum TabletMemtableFreezeState : int64_t {
  INVALID = 0,
  ACTIVE = 1,
  FREEZING = 2,
  READY_FOR_FLUSH = 3,
  FLUSHED = 4,
  RELEASED = 5,
  MAX_FREEZE_STATE
};

const static char *TABLET_MEMTABLE_FREEZE_STATE_TO_STR(const int64_t state)
{
  if (state >= TabletMemtableFreezeState::MAX_FREEZE_STATE) {
    return "";
  }
  STATIC_ASSERT(TabletMemtableFreezeState::INVALID == 0, "Invalid State Enum");
  STATIC_ASSERT(TabletMemtableFreezeState::ACTIVE == 1, "Invalid State Enum");
  STATIC_ASSERT(TabletMemtableFreezeState::FREEZING == 2, "Invalid State Enum");
  STATIC_ASSERT(TabletMemtableFreezeState::READY_FOR_FLUSH == 3, "Invalid State Enum");
  STATIC_ASSERT(TabletMemtableFreezeState::FLUSHED == 4, "Invalid State Enum");
  STATIC_ASSERT(TabletMemtableFreezeState::RELEASED == 5, "Invalid State Enum");
  const static char TABLET_MEMTABLE_FREEZE_STATE_TO_STR[6][20] = {"INVALID", "ACTIVE", "FREEZING", "READY_FOR_FLUSH", "FLUSHED", "RELEASED"};
  return TABLET_MEMTABLE_FREEZE_STATE_TO_STR[state];
}

class ObITabletMemtable : public ObIMemtable, public checkpoint::ObFreezeCheckpoint {
public:
#define DEF_REPORT_CHEKCPOINT_DIAGNOSE_INFO(function, update_function)                       \
  struct function {                                                                          \
  public:                                                                                    \
    function() {}                                                                            \
    function(const function &) = delete;                                                     \
    function &operator=(const function &) = delete;                                          \
    void operator()(const checkpoint::ObCheckpointDiagnoseParam &param) const                \
    {                                                                                        \
      checkpoint::ObCheckpointDiagnoseMgr *cdm = MTL(checkpoint::ObCheckpointDiagnoseMgr *); \
      if (OB_NOT_NULL(cdm)) {                                                                \
        cdm->update_function(param);                                                         \
      }                                                                                      \
    }                                                                                        \
  };
  DEF_REPORT_CHEKCPOINT_DIAGNOSE_INFO(UpdateStartGCTimeForMemtable, update_start_gc_time_for_memtable)
  DEF_REPORT_CHEKCPOINT_DIAGNOSE_INFO(AddCheckpointDiagnoseInfoForMemtable,
                                      add_diagnose_info<checkpoint::ObMemtableDiagnoseInfo>)

  template <class OP>
  void report_memtable_diagnose_info(const OP &op)
  {
    int ret = OB_SUCCESS;
    // logstream freeze
    if (!is_tablet_freeze()) {
      share::ObLSID ls_id;
      if (OB_FAIL(get_ls_id(ls_id))) {
        TRANS_LOG(WARN, "failed to get ls id", KPC(this));
      } else {
        checkpoint::ObCheckpointDiagnoseParam param(ls_id.id(), get_freeze_clock(), get_tablet_id(), (void *)this);
        op(param);
      }
    }
    // batch tablet freeze
    else if (checkpoint::INVALID_TRACE_ID != get_trace_id()) {
      checkpoint::ObCheckpointDiagnoseParam param(trace_id_, get_tablet_id(), (void *)this);
      op(param);
    }
  }

public:
  ObITabletMemtable()
      : allow_freeze_(true),
        is_tablet_freeze_(false),
        freeze_clock_(0),
        init_timestamp_(0),
        max_schema_version_(0),
        freezer_(nullptr),
        mt_stat_(),
        freeze_scn_(),
        max_end_scn_(),
        rec_scn_(),
        is_flushed_(false),
        logging_blocked_(false),
        resolved_active_memtable_left_boundary_(true),
        unset_active_memtable_logging_blocked_(false),
        read_barrier_(false),
        unsubmitted_cnt_(0),
        logging_blocked_start_time_(0),
        write_ref_cnt_(0),
        migration_clog_checkpoint_scn_(),
        freeze_state_(TabletMemtableFreezeState::INVALID),
        memtable_mgr_handle_()
  {
    max_end_scn_.set_min();
    rec_scn_.set_max();
    freeze_scn_.set_max();
    migration_clog_checkpoint_scn_.set_min();
  }

  void reset()
  {
    ObIMemtable::reset();
    ObFreezeCheckpoint::reset();
    allow_freeze_ = true;
    is_flushed_ = false;
    is_tablet_freeze_ = false;
    logging_blocked_ = false;
    resolved_active_memtable_left_boundary_ = true;
    unset_active_memtable_logging_blocked_ = false;
    read_barrier_ = false;
    freeze_clock_ = 0;
    freeze_state_ = TabletMemtableFreezeState::INVALID;
    unsubmitted_cnt_ = 0;
    logging_blocked_start_time_ = 0;
    init_timestamp_ = 0;
    max_schema_version_ = 0;
    max_end_scn_.set_min();
    rec_scn_.set_max();
    freeze_scn_.set_max();
    migration_clog_checkpoint_scn_.set_min();
    freezer_ = nullptr;
    memtable_mgr_handle_.reset();
    mt_stat_.reset();
  }

public:
  bool is_can_flush()
  {
    return TabletMemtableFreezeState::READY_FOR_FLUSH == freeze_state_ && share::SCN::max_scn() != get_end_scn();
  }
  virtual bool can_be_minor_merged() override;
  int inc_unsubmitted_cnt();
  int dec_unsubmitted_cnt();
  int set_freezer(ObFreezer *handler);
  int set_rec_scn(const share::SCN rec_scn);
  int set_migration_clog_checkpoint_scn(const share::SCN &clog_checkpoint_scn);
  int resolve_left_boundary(share::SCN end_scn) { return set_start_scn(end_scn); }
  int resolve_right_boundary();
  int set_start_scn(const share::SCN start_scn);
  int set_end_scn(const share::SCN end_scn);
  int set_max_end_scn(const share::SCN scn, bool allow_backoff = false);


public:  // derived from ObITable
  virtual bool is_active_memtable() override { return !is_frozen_memtable(); }
  virtual int64_t get_timestamp() const override { return init_timestamp_; }
  virtual int64_t dec_ref()
  {
    int64_t ref_cnt = ObITable::dec_ref();
    if (0 == ref_cnt) {
      report_memtable_diagnose_info(UpdateStartGCTimeForMemtable());
    }
    return ref_cnt;
  }

public:  // derived from ObIMemtable
  virtual int64_t inc_write_ref() override { return inc_write_ref_(); }
  virtual int64_t dec_write_ref() override { return dec_write_ref_(); }
  virtual int64_t get_write_ref() const override { return ATOMIC_LOAD(&write_ref_cnt_); }

public:  // derived from ObFreezeCheckpoint
  ObTabletID get_tablet_id() const { return key_.tablet_id_; }
  virtual bool is_active_checkpoint() override { return is_active_memtable(); }
  virtual bool is_frozen_checkpoint() override { return is_frozen_memtable(); }

public:
  // *************** pure virtual functions *****************
  virtual bool is_inited() const = 0;
  virtual int init(const ObITable::TableKey &table_key,
                   ObLSHandle &ls_handle,
                   ObFreezer *freezer,
                   ObTabletMemtableMgr *memtable_mgr,
                   const int64_t schema_version,
                   const uint32_t freeze_clock) = 0;
  virtual void print_ready_for_flush() = 0;
  virtual void set_allow_freeze(const bool allow_freeze) = 0;
  virtual int set_frozen() = 0;
  // *************** pure virtual functions *****************

public:
  // *************** setter *****************
  void set_max_schema_version(const int64_t schema_version);
  void set_is_tablet_freeze() { is_tablet_freeze_ = true; }
  void set_freeze_clock(const uint32_t freeze_clock) { ATOMIC_STORE(&freeze_clock_, freeze_clock); }
  void set_is_flushed() { is_flushed_ = true; }
  void set_read_barrier() { read_barrier_ = true; }
  void reset_mt_stat() { mt_stat_.reset(); }
  void unset_active_memtable_logging_blocked() { ATOMIC_STORE(&unset_active_memtable_logging_blocked_, true); }
  void set_frozen_time(const int64_t timestamp) const { mt_stat_.frozen_time_ = timestamp; }
  void set_last_print_time(const int64_t timestamp) const { mt_stat_.last_print_time_ = timestamp; }
  void set_ready_for_flush_time(const int64_t timestamp) { mt_stat_.ready_for_flush_time_= timestamp; }
  void set_create_flush_dag_time(const int64_t timestamp) { mt_stat_.create_flush_dag_time_ = timestamp; }
  void set_release_time(const int64_t timestamp) { mt_stat_.release_time_ = timestamp; }
  void set_push_table_into_gc_queue_time(const int64_t timestamp) { mt_stat_.push_table_into_gc_queue_time_ = timestamp; }
  void set_resolved_active_memtable_left_boundary(bool flag)
  {
    ATOMIC_STORE(&resolved_active_memtable_left_boundary_, flag);
  }
  void set_freeze_state(const TabletMemtableFreezeState state)
  {
    if (state >= TabletMemtableFreezeState::ACTIVE && state <= TabletMemtableFreezeState::RELEASED) {
      freeze_state_ = state;
    }
  }
  void set_logging_blocked()
  {
    logging_blocked_start_time_ = ObClockGenerator::getClock();
    ATOMIC_STORE(&logging_blocked_, true);
  }
  void unset_logging_blocked()
  {
    if (get_logging_blocked()) {
      ATOMIC_STORE(&logging_blocked_, false);
      int64_t cost_time = ObClockGenerator::getClock() - logging_blocked_start_time_;
      TRANS_LOG(INFO, "the cost time of logging blocked: ", K(cost_time), K(this), K(key_.tablet_id_));
    }
  }
  // *************** setter *****************

public:
  // *************** getter *****************
  bool get_is_flushed() { return is_flushed_; }
  bool is_tablet_freeze() { return is_tablet_freeze_; }
  bool &get_read_barrier() { return read_barrier_; }
  bool allow_freeze() const { return ATOMIC_LOAD(&allow_freeze_); }
  bool get_logging_blocked() { return ATOMIC_LOAD(&logging_blocked_); }
  bool get_resolved_active_memtable_left_boundary() { return ATOMIC_LOAD(&resolved_active_memtable_left_boundary_); }
  uint32_t get_freeze_clock() const { return ATOMIC_LOAD(&freeze_clock_); }
  int64_t get_unsubmitted_cnt() const { return ATOMIC_LOAD(&unsubmitted_cnt_); }
  int64_t get_max_schema_version() const ;
  int64_t get_frozen_time() const { return mt_stat_.frozen_time_; }
  int64_t get_last_print_time() const { return mt_stat_.last_print_time_; }
  TabletMemtableFreezeState get_freeze_state() const { return freeze_state_; }
  ObFreezer *get_freezer() { return freezer_; }
  ObMtStat &get_mt_stat() { return mt_stat_; }
  const ObMtStat &get_mt_stat() const { return mt_stat_; }
  share::SCN get_max_end_scn() const { return max_end_scn_.atomic_get(); }
  share::SCN get_rec_scn() { return rec_scn_.atomic_get(); }
  share::SCN get_migration_clog_checkpoint_scn() { return migration_clog_checkpoint_scn_.atomic_get(); }
  ObTabletMemtableMgr *get_memtable_mgr();
  // *************** getter *****************

  INHERIT_TO_STRING_KV("ObITable",
                       ObITable,
                       K(ls_id_),
                       K(allow_freeze_),
                       K(is_flushed_),
                       K(is_tablet_freeze_),
                       K(logging_blocked_),
                       K(resolved_active_memtable_left_boundary_),
                       K(unset_active_memtable_logging_blocked_),
                       K(read_barrier_),
                       K(freeze_clock_),
                       K(freeze_state_),
                       K(unsubmitted_cnt_),
                       K(init_timestamp_),
                       K(max_schema_version_),
                       K(write_ref_cnt_),
                       K(max_end_scn_),
                       K(rec_scn_),
                       K(freeze_scn_),
                       K(migration_clog_checkpoint_scn_),
                       KP(freezer_),
                       K(memtable_mgr_handle_),
                       K(mt_stat_.frozen_time_),
                       K(mt_stat_.ready_for_flush_time_),
                       K(mt_stat_.create_flush_dag_time_),
                       K(mt_stat_.release_time_),
                       K(mt_stat_.push_table_into_gc_queue_time_),
                       K(mt_stat_.last_print_time_))

protected:
  void resolve_left_boundary_for_active_memtable_();
  int get_ls_current_right_boundary_(share::SCN &current_right_boundary);
  int set_memtable_mgr_(ObTabletMemtableMgr *mgr);
  int64_t inc_unsubmitted_cnt_();
  int64_t dec_unsubmitted_cnt_();
  int64_t inc_write_ref_();
  int64_t dec_write_ref_();
  void unset_logging_blocked_for_active_memtable_();

protected:
  bool allow_freeze_;
  bool is_tablet_freeze_;
  mutable uint32_t freeze_clock_;
  int64_t init_timestamp_;
  int64_t max_schema_version_;  // to record the max schema version of memtable & schema_change_clog
  ObFreezer *freezer_;
  mutable ObMtStat mt_stat_;
  share::SCN freeze_scn_;
  share::SCN max_end_scn_;
  share::SCN rec_scn_;

private:
  bool is_flushed_;
  bool logging_blocked_;  // flag whether the memtable can submit log, cannot submit if true
  bool resolved_active_memtable_left_boundary_;
  bool unset_active_memtable_logging_blocked_;
  bool read_barrier_ CACHE_ALIGNED;
  int64_t unsubmitted_cnt_;
  int64_t logging_blocked_start_time_;  // record the start time of logging blocked
  int64_t write_ref_cnt_ CACHE_ALIGNED;
  share::SCN migration_clog_checkpoint_scn_;
  TabletMemtableFreezeState freeze_state_;
  ObMemtableMgrHandle memtable_mgr_handle_;
};




}  // namespace storage
}  // namespace oceanbase

#endif