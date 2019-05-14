#pragma once
#include "../NovusTypes.h"
#include "../Opcodes.h"
#include "../Offsets.h"

class DataStore;
typedef void(__cdecl ClientServices_SendPacket)(DataStore* dataStore);
ClientServices_SendPacket* SendPacket_1 = (ClientServices_SendPacket*)Offsets::ClientServicesSendPacket;

typedef DataStore* (__thiscall* InitializePtr)(DataStore* pData);
typedef DataStore& (__thiscall* PutInt8Ptr)(DataStore* pData, i8 val);
typedef DataStore& (__thiscall* PutInt16Ptr)(DataStore* pData, i16 val);
typedef DataStore& (__thiscall* PutInt32Ptr)(DataStore* pData, i32 val);
typedef DataStore& (__thiscall* PutInt64Ptr)(DataStore* pData, i64 val);
typedef DataStore& (__thiscall* PutFloatPtr)(DataStore* pData, f32 val);
typedef DataStore& (__thiscall* PutStringPtr)(DataStore* pData, char const* pString);
typedef DataStore& (__thiscall* PutBytesPtr)(DataStore* pData, u8* pBuf, u32 size);

typedef DataStore& (__thiscall* GetInt8Ptr)(DataStore* pData, i8& val);
typedef DataStore& (__thiscall* GetInt16Ptr)(DataStore* pData, i16& val);
typedef DataStore& (__thiscall* GetInt32Ptr)(DataStore* pData, i32& val);
typedef DataStore& (__thiscall* GetInt64Ptr)(DataStore* pData, i64& val);
typedef DataStore& (__thiscall* GetFloatPtr)(DataStore* pData, f32& val);
typedef DataStore& (__thiscall* GetStringPtr)(DataStore* pData, char* pString, u32 maxChars);
typedef DataStore& (__thiscall* GetBytesPtr)(DataStore* pData, u8* pBuf, u32 numBytes);

typedef void(__thiscall* FinalizePtr)(DataStore* pData);
typedef void(__thiscall* DestroyPtr)(DataStore* pData);

class DataStore
{
private:
    void* vTable;
    u8* m_buffer;
    u32 m_base;
    u32 m_alloc;
    u32 m_size;
    u32 m_read;

    static InitializePtr fpInit;
    static PutInt8Ptr fpPutInt8;
    static PutInt16Ptr fpPutInt16;
    static PutInt32Ptr fpPutInt32;
    static PutInt64Ptr fpPutInt64;
    static PutFloatPtr fpPutFloat;
    static PutStringPtr fpPutString;
    static PutBytesPtr fpPutBytes;
    static GetInt8Ptr fpGetInt8;
    static GetInt16Ptr fpGetInt16;
    static GetInt32Ptr fpGetInt32;
    static GetInt64Ptr fpGetInt64;
    static GetFloatPtr fpGetFloat;
    static GetStringPtr fpGetString;
    static GetBytesPtr fpGetBytes;
    static FinalizePtr fpFinalize;
    static DestroyPtr fpDestroy;

public:
    DataStore() { fpInit(this); }
    ~DataStore() { fpDestroy(this); }
    DataStore(Opcode msg) { fpInit(this); fpPutInt32(this, msg); }

    DataStore& PutInt8(i8 val) { return fpPutInt8(this, val); }
    DataStore& PutInt16(i16 val) { return fpPutInt16(this, val); }
    DataStore& PutInt32(i32 val) { return fpPutInt32(this, val); }
    DataStore& PutInt64(i64 val) { return fpPutInt64(this, val); }
    DataStore& PutFloat(f32 val) { return fpPutFloat(this, val); }
    DataStore& PutString(char const* pString) { return fpPutString(this, pString); }
    DataStore& PutPutBytes(u8* pBuf, u32 size) { return fpPutBytes(this, pBuf, size); }

    DataStore& GetInt8(i8& val) { return fpGetInt8(this, val); }
    DataStore& GetInt16(i16& val) { return fpGetInt16(this, val); }
    DataStore& GetInt32(i32& val) { return fpGetInt32(this, val); }
    DataStore& GetInt64(i64& val) { return fpGetInt64(this, val); }
    DataStore& GetFloat(f32& val) { return fpGetFloat(this, val); }
    DataStore& GetString(char* pString, u32 maxChars) { return fpGetString(this, pString, maxChars); }
    DataStore& GetBytes(u8* pBuf, u32 numBytes) { return fpGetBytes(this, pBuf, numBytes); }

    void Finalize() { fpFinalize(this); }
    void SendPacket() { Finalize(); SendPacket_1(this); }
};

DataStore* (__thiscall* DataStore::fpInit)(DataStore* pData) = reinterpret_cast<InitializePtr>(Offsets::CDataStoreGenPacket);

DataStore& (__thiscall* DataStore::fpPutInt8)(DataStore* pData, i8 val) = reinterpret_cast<PutInt8Ptr>(Offsets::CDataStorePutI8);
DataStore& (__thiscall* DataStore::fpPutInt16)(DataStore* pData, i16 val) = reinterpret_cast<PutInt16Ptr>(Offsets::CDataStorePutI16);
DataStore& (__thiscall* DataStore::fpPutInt32)(DataStore* pData, i32 val) = reinterpret_cast<PutInt32Ptr>(Offsets::CDataStorePutI32);
DataStore& (__thiscall* DataStore::fpPutInt64)(DataStore* pData, i64 val) = reinterpret_cast<PutInt64Ptr>(Offsets::CDataStorePutI64);
DataStore& (__thiscall* DataStore::fpPutFloat)(DataStore* pData, f32 val) = reinterpret_cast<PutFloatPtr>(Offsets::CDataStorePutF32);
DataStore& (__thiscall* DataStore::fpPutString)(DataStore* pData, char const* pString) = reinterpret_cast<PutStringPtr>(Offsets::CDataStorePutString);
DataStore& (__thiscall* DataStore::fpPutBytes)(DataStore* pData, u8* pBuf, u32 size) = reinterpret_cast<PutBytesPtr>(Offsets::CDataStorePutBytes);

DataStore& (__thiscall* DataStore::fpGetInt8)(DataStore* pData, i8& val) = reinterpret_cast<GetInt8Ptr>(Offsets::CDataStoreGetI8);
DataStore& (__thiscall* DataStore::fpGetInt16)(DataStore* pData, i16& val) = reinterpret_cast<GetInt16Ptr>(Offsets::CDataStoreGetI16);
DataStore& (__thiscall* DataStore::fpGetInt32)(DataStore* pData, i32& val) = reinterpret_cast<GetInt32Ptr>(Offsets::CDataStoreGetI32);
DataStore& (__thiscall* DataStore::fpGetInt64)(DataStore* pData, i64& val) = reinterpret_cast<GetInt64Ptr>(Offsets::CDataStoreGetI64);
DataStore& (__thiscall* DataStore::fpGetFloat)(DataStore* pData, f32& val) = reinterpret_cast<GetFloatPtr>(Offsets::CDataStoreGetF32);
DataStore& (__thiscall* DataStore::fpGetString)(DataStore* pData, char* pString, u32 maxChars) = reinterpret_cast<GetStringPtr>(Offsets::CDataStoreGetString);
DataStore& (__thiscall* DataStore::fpGetBytes)(DataStore* pData, u8* pBuf, u32 numBytes) = reinterpret_cast<GetBytesPtr>(Offsets::CDataStoreGetBytes);

void(__thiscall* DataStore::fpFinalize)(DataStore* pData) = reinterpret_cast<FinalizePtr>(Offsets::CDataStoreFinalize);
void(__thiscall* DataStore::fpDestroy)(DataStore* pData) = reinterpret_cast<DestroyPtr>(Offsets::CDataStoreDestroy);