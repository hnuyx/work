// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: data.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_data_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_data_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_data_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_data_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[3]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_data_2eproto;
namespace tdpkg {
class Data;
class DataDefaultTypeInternal;
extern DataDefaultTypeInternal _Data_default_instance_;
class DataReq;
class DataReqDefaultTypeInternal;
extern DataReqDefaultTypeInternal _DataReq_default_instance_;
class DataResp;
class DataRespDefaultTypeInternal;
extern DataRespDefaultTypeInternal _DataResp_default_instance_;
}  // namespace tdpkg
PROTOBUF_NAMESPACE_OPEN
template<> ::tdpkg::Data* Arena::CreateMaybeMessage<::tdpkg::Data>(Arena*);
template<> ::tdpkg::DataReq* Arena::CreateMaybeMessage<::tdpkg::DataReq>(Arena*);
template<> ::tdpkg::DataResp* Arena::CreateMaybeMessage<::tdpkg::DataResp>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace tdpkg {

// ===================================================================

class DataReq :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tdpkg.DataReq) */ {
 public:
  DataReq();
  virtual ~DataReq();

  DataReq(const DataReq& from);
  DataReq(DataReq&& from) noexcept
    : DataReq() {
    *this = ::std::move(from);
  }

  inline DataReq& operator=(const DataReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline DataReq& operator=(DataReq&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const DataReq& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DataReq* internal_default_instance() {
    return reinterpret_cast<const DataReq*>(
               &_DataReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(DataReq& a, DataReq& b) {
    a.Swap(&b);
  }
  inline void Swap(DataReq* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline DataReq* New() const final {
    return CreateMaybeMessage<DataReq>(nullptr);
  }

  DataReq* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<DataReq>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const DataReq& from);
  void MergeFrom(const DataReq& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DataReq* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tdpkg.DataReq";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_data_2eproto);
    return ::descriptor_table_data_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kRcFieldNumber = 3,
    kRaFieldNumber = 1,
    kRbFieldNumber = 2,
  };
  // string rc = 3;
  void clear_rc();
  const std::string& rc() const;
  void set_rc(const std::string& value);
  void set_rc(std::string&& value);
  void set_rc(const char* value);
  void set_rc(const char* value, size_t size);
  std::string* mutable_rc();
  std::string* release_rc();
  void set_allocated_rc(std::string* rc);
  private:
  const std::string& _internal_rc() const;
  void _internal_set_rc(const std::string& value);
  std::string* _internal_mutable_rc();
  public:

  // int32 ra = 1;
  void clear_ra();
  ::PROTOBUF_NAMESPACE_ID::int32 ra() const;
  void set_ra(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_ra() const;
  void _internal_set_ra(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // uint32 rb = 2;
  void clear_rb();
  ::PROTOBUF_NAMESPACE_ID::uint32 rb() const;
  void set_rb(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_rb() const;
  void _internal_set_rb(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:tdpkg.DataReq)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr rc_;
  ::PROTOBUF_NAMESPACE_ID::int32 ra_;
  ::PROTOBUF_NAMESPACE_ID::uint32 rb_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_data_2eproto;
};
// -------------------------------------------------------------------

class Data :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tdpkg.Data) */ {
 public:
  Data();
  virtual ~Data();

  Data(const Data& from);
  Data(Data&& from) noexcept
    : Data() {
    *this = ::std::move(from);
  }

  inline Data& operator=(const Data& from) {
    CopyFrom(from);
    return *this;
  }
  inline Data& operator=(Data&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const Data& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Data* internal_default_instance() {
    return reinterpret_cast<const Data*>(
               &_Data_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Data& a, Data& b) {
    a.Swap(&b);
  }
  inline void Swap(Data* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Data* New() const final {
    return CreateMaybeMessage<Data>(nullptr);
  }

  Data* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Data>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Data& from);
  void MergeFrom(const Data& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Data* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tdpkg.Data";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_data_2eproto);
    return ::descriptor_table_data_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDeFieldNumber = 5,
    kDaFieldNumber = 1,
    kDbFieldNumber = 2,
    kDcFieldNumber = 3,
    kDdFieldNumber = 4,
  };
  // string de = 5;
  void clear_de();
  const std::string& de() const;
  void set_de(const std::string& value);
  void set_de(std::string&& value);
  void set_de(const char* value);
  void set_de(const char* value, size_t size);
  std::string* mutable_de();
  std::string* release_de();
  void set_allocated_de(std::string* de);
  private:
  const std::string& _internal_de() const;
  void _internal_set_de(const std::string& value);
  std::string* _internal_mutable_de();
  public:

  // int64 da = 1;
  void clear_da();
  ::PROTOBUF_NAMESPACE_ID::int64 da() const;
  void set_da(::PROTOBUF_NAMESPACE_ID::int64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int64 _internal_da() const;
  void _internal_set_da(::PROTOBUF_NAMESPACE_ID::int64 value);
  public:

  // uint64 db = 2;
  void clear_db();
  ::PROTOBUF_NAMESPACE_ID::uint64 db() const;
  void set_db(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_db() const;
  void _internal_set_db(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // int32 dc = 3;
  void clear_dc();
  ::PROTOBUF_NAMESPACE_ID::int32 dc() const;
  void set_dc(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_dc() const;
  void _internal_set_dc(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // uint32 dd = 4;
  void clear_dd();
  ::PROTOBUF_NAMESPACE_ID::uint32 dd() const;
  void set_dd(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_dd() const;
  void _internal_set_dd(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:tdpkg.Data)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr de_;
  ::PROTOBUF_NAMESPACE_ID::int64 da_;
  ::PROTOBUF_NAMESPACE_ID::uint64 db_;
  ::PROTOBUF_NAMESPACE_ID::int32 dc_;
  ::PROTOBUF_NAMESPACE_ID::uint32 dd_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_data_2eproto;
};
// -------------------------------------------------------------------

class DataResp :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:tdpkg.DataResp) */ {
 public:
  DataResp();
  virtual ~DataResp();

  DataResp(const DataResp& from);
  DataResp(DataResp&& from) noexcept
    : DataResp() {
    *this = ::std::move(from);
  }

  inline DataResp& operator=(const DataResp& from) {
    CopyFrom(from);
    return *this;
  }
  inline DataResp& operator=(DataResp&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const DataResp& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const DataResp* internal_default_instance() {
    return reinterpret_cast<const DataResp*>(
               &_DataResp_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(DataResp& a, DataResp& b) {
    a.Swap(&b);
  }
  inline void Swap(DataResp* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline DataResp* New() const final {
    return CreateMaybeMessage<DataResp>(nullptr);
  }

  DataResp* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<DataResp>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const DataResp& from);
  void MergeFrom(const DataResp& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DataResp* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "tdpkg.DataResp";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_data_2eproto);
    return ::descriptor_table_data_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kDatasFieldNumber = 7,
    kRscFieldNumber = 3,
    kRsaFieldNumber = 1,
    kRsbFieldNumber = 2,
  };
  // repeated .tdpkg.Data datas = 7;
  int datas_size() const;
  private:
  int _internal_datas_size() const;
  public:
  void clear_datas();
  ::tdpkg::Data* mutable_datas(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tdpkg::Data >*
      mutable_datas();
  private:
  const ::tdpkg::Data& _internal_datas(int index) const;
  ::tdpkg::Data* _internal_add_datas();
  public:
  const ::tdpkg::Data& datas(int index) const;
  ::tdpkg::Data* add_datas();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tdpkg::Data >&
      datas() const;

  // string rsc = 3;
  void clear_rsc();
  const std::string& rsc() const;
  void set_rsc(const std::string& value);
  void set_rsc(std::string&& value);
  void set_rsc(const char* value);
  void set_rsc(const char* value, size_t size);
  std::string* mutable_rsc();
  std::string* release_rsc();
  void set_allocated_rsc(std::string* rsc);
  private:
  const std::string& _internal_rsc() const;
  void _internal_set_rsc(const std::string& value);
  std::string* _internal_mutable_rsc();
  public:

  // int32 rsa = 1;
  void clear_rsa();
  ::PROTOBUF_NAMESPACE_ID::int32 rsa() const;
  void set_rsa(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_rsa() const;
  void _internal_set_rsa(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // uint32 rsb = 2;
  void clear_rsb();
  ::PROTOBUF_NAMESPACE_ID::uint32 rsb() const;
  void set_rsb(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_rsb() const;
  void _internal_set_rsb(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:tdpkg.DataResp)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tdpkg::Data > datas_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr rsc_;
  ::PROTOBUF_NAMESPACE_ID::int32 rsa_;
  ::PROTOBUF_NAMESPACE_ID::uint32 rsb_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_data_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// DataReq

// int32 ra = 1;
inline void DataReq::clear_ra() {
  ra_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 DataReq::_internal_ra() const {
  return ra_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 DataReq::ra() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataReq.ra)
  return _internal_ra();
}
inline void DataReq::_internal_set_ra(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  ra_ = value;
}
inline void DataReq::set_ra(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_ra(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataReq.ra)
}

// uint32 rb = 2;
inline void DataReq::clear_rb() {
  rb_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 DataReq::_internal_rb() const {
  return rb_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 DataReq::rb() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataReq.rb)
  return _internal_rb();
}
inline void DataReq::_internal_set_rb(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  rb_ = value;
}
inline void DataReq::set_rb(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_rb(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataReq.rb)
}

// string rc = 3;
inline void DataReq::clear_rc() {
  rc_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& DataReq::rc() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataReq.rc)
  return _internal_rc();
}
inline void DataReq::set_rc(const std::string& value) {
  _internal_set_rc(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataReq.rc)
}
inline std::string* DataReq::mutable_rc() {
  // @@protoc_insertion_point(field_mutable:tdpkg.DataReq.rc)
  return _internal_mutable_rc();
}
inline const std::string& DataReq::_internal_rc() const {
  return rc_.GetNoArena();
}
inline void DataReq::_internal_set_rc(const std::string& value) {
  
  rc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void DataReq::set_rc(std::string&& value) {
  
  rc_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tdpkg.DataReq.rc)
}
inline void DataReq::set_rc(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  rc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tdpkg.DataReq.rc)
}
inline void DataReq::set_rc(const char* value, size_t size) {
  
  rc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tdpkg.DataReq.rc)
}
inline std::string* DataReq::_internal_mutable_rc() {
  
  return rc_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* DataReq::release_rc() {
  // @@protoc_insertion_point(field_release:tdpkg.DataReq.rc)
  
  return rc_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void DataReq::set_allocated_rc(std::string* rc) {
  if (rc != nullptr) {
    
  } else {
    
  }
  rc_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), rc);
  // @@protoc_insertion_point(field_set_allocated:tdpkg.DataReq.rc)
}

// -------------------------------------------------------------------

// Data

// int64 da = 1;
inline void Data::clear_da() {
  da_ = PROTOBUF_LONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Data::_internal_da() const {
  return da_;
}
inline ::PROTOBUF_NAMESPACE_ID::int64 Data::da() const {
  // @@protoc_insertion_point(field_get:tdpkg.Data.da)
  return _internal_da();
}
inline void Data::_internal_set_da(::PROTOBUF_NAMESPACE_ID::int64 value) {
  
  da_ = value;
}
inline void Data::set_da(::PROTOBUF_NAMESPACE_ID::int64 value) {
  _internal_set_da(value);
  // @@protoc_insertion_point(field_set:tdpkg.Data.da)
}

// uint64 db = 2;
inline void Data::clear_db() {
  db_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Data::_internal_db() const {
  return db_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 Data::db() const {
  // @@protoc_insertion_point(field_get:tdpkg.Data.db)
  return _internal_db();
}
inline void Data::_internal_set_db(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  db_ = value;
}
inline void Data::set_db(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_db(value);
  // @@protoc_insertion_point(field_set:tdpkg.Data.db)
}

// int32 dc = 3;
inline void Data::clear_dc() {
  dc_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Data::_internal_dc() const {
  return dc_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Data::dc() const {
  // @@protoc_insertion_point(field_get:tdpkg.Data.dc)
  return _internal_dc();
}
inline void Data::_internal_set_dc(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  dc_ = value;
}
inline void Data::set_dc(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_dc(value);
  // @@protoc_insertion_point(field_set:tdpkg.Data.dc)
}

// uint32 dd = 4;
inline void Data::clear_dd() {
  dd_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Data::_internal_dd() const {
  return dd_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Data::dd() const {
  // @@protoc_insertion_point(field_get:tdpkg.Data.dd)
  return _internal_dd();
}
inline void Data::_internal_set_dd(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  dd_ = value;
}
inline void Data::set_dd(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_dd(value);
  // @@protoc_insertion_point(field_set:tdpkg.Data.dd)
}

// string de = 5;
inline void Data::clear_de() {
  de_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& Data::de() const {
  // @@protoc_insertion_point(field_get:tdpkg.Data.de)
  return _internal_de();
}
inline void Data::set_de(const std::string& value) {
  _internal_set_de(value);
  // @@protoc_insertion_point(field_set:tdpkg.Data.de)
}
inline std::string* Data::mutable_de() {
  // @@protoc_insertion_point(field_mutable:tdpkg.Data.de)
  return _internal_mutable_de();
}
inline const std::string& Data::_internal_de() const {
  return de_.GetNoArena();
}
inline void Data::_internal_set_de(const std::string& value) {
  
  de_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void Data::set_de(std::string&& value) {
  
  de_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tdpkg.Data.de)
}
inline void Data::set_de(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  de_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tdpkg.Data.de)
}
inline void Data::set_de(const char* value, size_t size) {
  
  de_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tdpkg.Data.de)
}
inline std::string* Data::_internal_mutable_de() {
  
  return de_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* Data::release_de() {
  // @@protoc_insertion_point(field_release:tdpkg.Data.de)
  
  return de_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void Data::set_allocated_de(std::string* de) {
  if (de != nullptr) {
    
  } else {
    
  }
  de_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), de);
  // @@protoc_insertion_point(field_set_allocated:tdpkg.Data.de)
}

// -------------------------------------------------------------------

// DataResp

// int32 rsa = 1;
inline void DataResp::clear_rsa() {
  rsa_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 DataResp::_internal_rsa() const {
  return rsa_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 DataResp::rsa() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataResp.rsa)
  return _internal_rsa();
}
inline void DataResp::_internal_set_rsa(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  rsa_ = value;
}
inline void DataResp::set_rsa(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_rsa(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataResp.rsa)
}

// uint32 rsb = 2;
inline void DataResp::clear_rsb() {
  rsb_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 DataResp::_internal_rsb() const {
  return rsb_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 DataResp::rsb() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataResp.rsb)
  return _internal_rsb();
}
inline void DataResp::_internal_set_rsb(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  rsb_ = value;
}
inline void DataResp::set_rsb(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_rsb(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataResp.rsb)
}

// string rsc = 3;
inline void DataResp::clear_rsc() {
  rsc_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& DataResp::rsc() const {
  // @@protoc_insertion_point(field_get:tdpkg.DataResp.rsc)
  return _internal_rsc();
}
inline void DataResp::set_rsc(const std::string& value) {
  _internal_set_rsc(value);
  // @@protoc_insertion_point(field_set:tdpkg.DataResp.rsc)
}
inline std::string* DataResp::mutable_rsc() {
  // @@protoc_insertion_point(field_mutable:tdpkg.DataResp.rsc)
  return _internal_mutable_rsc();
}
inline const std::string& DataResp::_internal_rsc() const {
  return rsc_.GetNoArena();
}
inline void DataResp::_internal_set_rsc(const std::string& value) {
  
  rsc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void DataResp::set_rsc(std::string&& value) {
  
  rsc_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tdpkg.DataResp.rsc)
}
inline void DataResp::set_rsc(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  rsc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tdpkg.DataResp.rsc)
}
inline void DataResp::set_rsc(const char* value, size_t size) {
  
  rsc_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tdpkg.DataResp.rsc)
}
inline std::string* DataResp::_internal_mutable_rsc() {
  
  return rsc_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* DataResp::release_rsc() {
  // @@protoc_insertion_point(field_release:tdpkg.DataResp.rsc)
  
  return rsc_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void DataResp::set_allocated_rsc(std::string* rsc) {
  if (rsc != nullptr) {
    
  } else {
    
  }
  rsc_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), rsc);
  // @@protoc_insertion_point(field_set_allocated:tdpkg.DataResp.rsc)
}

// repeated .tdpkg.Data datas = 7;
inline int DataResp::_internal_datas_size() const {
  return datas_.size();
}
inline int DataResp::datas_size() const {
  return _internal_datas_size();
}
inline void DataResp::clear_datas() {
  datas_.Clear();
}
inline ::tdpkg::Data* DataResp::mutable_datas(int index) {
  // @@protoc_insertion_point(field_mutable:tdpkg.DataResp.datas)
  return datas_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tdpkg::Data >*
DataResp::mutable_datas() {
  // @@protoc_insertion_point(field_mutable_list:tdpkg.DataResp.datas)
  return &datas_;
}
inline const ::tdpkg::Data& DataResp::_internal_datas(int index) const {
  return datas_.Get(index);
}
inline const ::tdpkg::Data& DataResp::datas(int index) const {
  // @@protoc_insertion_point(field_get:tdpkg.DataResp.datas)
  return _internal_datas(index);
}
inline ::tdpkg::Data* DataResp::_internal_add_datas() {
  return datas_.Add();
}
inline ::tdpkg::Data* DataResp::add_datas() {
  // @@protoc_insertion_point(field_add:tdpkg.DataResp.datas)
  return _internal_add_datas();
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::tdpkg::Data >&
DataResp::datas() const {
  // @@protoc_insertion_point(field_list:tdpkg.DataResp.datas)
  return datas_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace tdpkg

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_data_2eproto