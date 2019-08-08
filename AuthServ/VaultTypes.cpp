/******************************************************************************
 * This file is part of dirtsand.                                             *
 *                                                                            *
 * dirtsand is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU Affero General Public License as             *
 * published by the Free Software Foundation, either version 3 of the         *
 * License, or (at your option) any later version.                            *
 *                                                                            *
 * dirtsand is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Affero General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the GNU Affero General Public License   *
 * along with dirtsand.  If not, see <http://www.gnu.org/licenses/>.          *
 ******************************************************************************/

#include "VaultTypes.h"
#include "errors.h"

#define READ_VAULT_STRING(value) \
    { \
        uint32_t length = stream->read<uint32_t>(); \
        if ((length % sizeof(char16_t)) != 0) \
            throw DS::MalformedData(); \
        ST::utf16_buffer buffer; \
        buffer.allocate(length / sizeof(char16_t)); \
        stream->readBytes(buffer.data(), length); \
        value = ST::string::from_utf16(buffer, ST::substitute_invalid); \
    }

#define WRITE_VAULT_STRING(value) \
    { \
        ST::utf16_buffer wbuf = value.to_utf16(); \
        stream->write<uint32_t>((wbuf.size() + 1) * sizeof(char16_t)); \
        stream->writeBytes(wbuf.data(), wbuf.size() * sizeof(char16_t)); \
        stream->write<char16_t>(0); \
    }

void DS::Vault::Node::read(DS::Stream* stream)
{
    m_fields = stream->read<uint64_t>();
    if (m_fields & e_FieldNodeIdx)
        m_NodeIdx = stream->read<uint32_t>();
    if (m_fields & e_FieldCreateTime)
        m_CreateTime = stream->read<uint32_t>();
    if (m_fields & e_FieldModifyTime)
        m_ModifyTime = stream->read<uint32_t>();
    if (m_fields & e_FieldCreateAgeName)
        READ_VAULT_STRING(m_CreateAgeName);
    if (m_fields & e_FieldCreateAgeUuid)
        m_CreateAgeUuid.read(stream);
    if (m_fields & e_FieldCreatorUuid)
        m_CreatorUuid.read(stream);
    if (m_fields & e_FieldCreatorIdx)
        m_CreatorIdx = stream->read<uint32_t>();
    if (m_fields & e_FieldNodeType)
        m_NodeType = stream->read<int32_t>();
    if (m_fields & e_FieldInt32_1)
        m_Int32_1 = stream->read<int32_t>();
    if (m_fields & e_FieldInt32_2)
        m_Int32_2 = stream->read<int32_t>();
    if (m_fields & e_FieldInt32_3)
        m_Int32_3 = stream->read<int32_t>();
    if (m_fields & e_FieldInt32_4)
        m_Int32_4 = stream->read<int32_t>();
    if (m_fields & e_FieldUint32_1)
        m_Uint32_1 = stream->read<uint32_t>();
    if (m_fields & e_FieldUint32_2)
        m_Uint32_2 = stream->read<uint32_t>();
    if (m_fields & e_FieldUint32_3)
        m_Uint32_3 = stream->read<uint32_t>();
    if (m_fields & e_FieldUint32_4)
        m_Uint32_4 = stream->read<uint32_t>();
    if (m_fields & e_FieldUuid_1)
        m_Uuid_1.read(stream);
    if (m_fields & e_FieldUuid_2)
        m_Uuid_2.read(stream);
    if (m_fields & e_FieldUuid_3)
        m_Uuid_3.read(stream);
    if (m_fields & e_FieldUuid_4)
        m_Uuid_4.read(stream);
    if (m_fields & e_FieldString64_1)
        READ_VAULT_STRING(m_String64_1);
    if (m_fields & e_FieldString64_2)
        READ_VAULT_STRING(m_String64_2);
    if (m_fields & e_FieldString64_3)
        READ_VAULT_STRING(m_String64_3);
    if (m_fields & e_FieldString64_4)
        READ_VAULT_STRING(m_String64_4);
    if (m_fields & e_FieldString64_5)
        READ_VAULT_STRING(m_String64_5);
    if (m_fields & e_FieldString64_6)
        READ_VAULT_STRING(m_String64_6);
    if (m_fields & e_FieldIString64_1)
        READ_VAULT_STRING(m_IString64_1);
    if (m_fields & e_FieldIString64_2)
        READ_VAULT_STRING(m_IString64_2);
    if (m_fields & e_FieldText_1)
        READ_VAULT_STRING(m_Text_1);
    if (m_fields & e_FieldText_2)
        READ_VAULT_STRING(m_Text_2);
    if (m_fields & e_FieldBlob_1) {
        uint32_t size = stream->read<uint32_t>();
        uint8_t* data = new uint8_t[size];
        stream->readBytes(data, size);
        m_Blob_1 = DS::Blob::Steal(data, size);
    }
    if (m_fields & e_FieldBlob_2) {
        uint32_t size = stream->read<uint32_t>();
        uint8_t* data = new uint8_t[size];
        stream->readBytes(data, size);
        m_Blob_2 = DS::Blob::Steal(data, size);
    }
}

void DS::Vault::Node::write(DS::Stream* stream) const
{
    stream->write<uint64_t>(m_fields);
    if (m_fields & e_FieldNodeIdx)
        stream->write<uint32_t>(m_NodeIdx);
    if (m_fields & e_FieldCreateTime)
        stream->write<uint32_t>(m_CreateTime);
    if (m_fields & e_FieldModifyTime)
        stream->write<uint32_t>(m_ModifyTime);
    if (m_fields & e_FieldCreateAgeName)
        WRITE_VAULT_STRING(m_CreateAgeName);
    if (m_fields & e_FieldCreateAgeUuid)
        m_CreateAgeUuid.write(stream);
    if (m_fields & e_FieldCreatorUuid)
        m_CreatorUuid.write(stream);
    if (m_fields & e_FieldCreatorIdx)
        stream->write<uint32_t>(m_CreatorIdx);
    if (m_fields & e_FieldNodeType)
        stream->write<int32_t>(m_NodeType);
    if (m_fields & e_FieldInt32_1)
        stream->write<int32_t>(m_Int32_1);
    if (m_fields & e_FieldInt32_2)
        stream->write<int32_t>(m_Int32_2);
    if (m_fields & e_FieldInt32_3)
        stream->write<int32_t>(m_Int32_3);
    if (m_fields & e_FieldInt32_4)
        stream->write<int32_t>(m_Int32_4);
    if (m_fields & e_FieldUint32_1)
        stream->write<uint32_t>(m_Uint32_1);
    if (m_fields & e_FieldUint32_2)
        stream->write<uint32_t>(m_Uint32_2);
    if (m_fields & e_FieldUint32_3)
        stream->write<uint32_t>(m_Uint32_3);
    if (m_fields & e_FieldUint32_4)
        stream->write<uint32_t>(m_Uint32_4);
    if (m_fields & e_FieldUuid_1)
        m_Uuid_1.write(stream);
    if (m_fields & e_FieldUuid_2)
        m_Uuid_2.write(stream);
    if (m_fields & e_FieldUuid_3)
        m_Uuid_3.write(stream);
    if (m_fields & e_FieldUuid_4)
        m_Uuid_4.write(stream);
    if (m_fields & e_FieldString64_1)
        WRITE_VAULT_STRING(m_String64_1);
    if (m_fields & e_FieldString64_2)
        WRITE_VAULT_STRING(m_String64_2);
    if (m_fields & e_FieldString64_3)
        WRITE_VAULT_STRING(m_String64_3);
    if (m_fields & e_FieldString64_4)
        WRITE_VAULT_STRING(m_String64_4);
    if (m_fields & e_FieldString64_5)
        WRITE_VAULT_STRING(m_String64_5);
    if (m_fields & e_FieldString64_6)
        WRITE_VAULT_STRING(m_String64_6);
    if (m_fields & e_FieldIString64_1)
        WRITE_VAULT_STRING(m_IString64_1);
    if (m_fields & e_FieldIString64_2)
        WRITE_VAULT_STRING(m_IString64_2);
    if (m_fields & e_FieldText_1)
        WRITE_VAULT_STRING(m_Text_1);
    if (m_fields & e_FieldText_2)
        WRITE_VAULT_STRING(m_Text_2);
    if (m_fields & e_FieldBlob_1) {
        stream->write<uint32_t>(m_Blob_1.size());
        stream->writeBytes(m_Blob_1.buffer(), m_Blob_1.size());
    }
    if (m_fields & e_FieldBlob_2) {
        stream->write<uint32_t>(m_Blob_2.size());
        stream->writeBytes(m_Blob_2.buffer(), m_Blob_2.size());
    }
}

DS::Vault::Node DS::Vault::Node::copy() const
{
    DS::Vault::Node dup;
    dup.m_fields = m_fields;
    if (m_fields & e_FieldNodeIdx)
        dup.m_NodeIdx = m_NodeIdx;
    if (m_fields & e_FieldCreateTime)
        dup.m_CreateTime = m_CreateTime;
    if (m_fields & e_FieldModifyTime)
        dup.m_ModifyTime = m_ModifyTime;
    if (m_fields & e_FieldCreateAgeName)
        dup.m_CreateAgeName = m_CreateAgeName;
    if (m_fields & e_FieldCreateAgeUuid)
        dup.m_CreateAgeUuid = m_CreateAgeUuid;
    if (m_fields & e_FieldCreatorUuid)
        dup.m_CreatorUuid = m_CreatorUuid;
    if (m_fields & e_FieldCreatorIdx)
        dup.m_CreatorIdx = m_CreatorIdx;
    if (m_fields & e_FieldNodeType)
        dup.m_NodeType = m_NodeType;
    if (m_fields & e_FieldInt32_1)
        dup.m_Int32_1 = m_Int32_1;
    if (m_fields & e_FieldInt32_2)
        dup.m_Int32_2 = m_Int32_2;
    if (m_fields & e_FieldInt32_3)
        dup.m_Int32_3 = m_Int32_3;
    if (m_fields & e_FieldInt32_4)
        dup.m_Int32_4 = m_Int32_4;
    if (m_fields & e_FieldUint32_1)
        dup.m_Uint32_1 = m_Uint32_1;
    if (m_fields & e_FieldUint32_2)
        dup.m_Uint32_2 = m_Uint32_2;
    if (m_fields & e_FieldUint32_3)
        dup.m_Uint32_3 = m_Uint32_3;
    if (m_fields & e_FieldUint32_4)
        dup.m_Uint32_4 = m_Uint32_4;
    if (m_fields & e_FieldUuid_1)
        dup.m_Uuid_1 = m_Uuid_1;
    if (m_fields & e_FieldUuid_2)
        dup.m_Uuid_2 = m_Uuid_2;
    if (m_fields & e_FieldUuid_3)
        dup.m_Uuid_3 = m_Uuid_3;
    if (m_fields & e_FieldUuid_4)
        dup.m_Uuid_4 = m_Uuid_4;
    if (m_fields & e_FieldString64_1)
        dup.m_String64_1 = m_String64_1;
    if (m_fields & e_FieldString64_2)
        dup.m_String64_2 = m_String64_2;
    if (m_fields & e_FieldString64_3)
        dup.m_String64_3 = m_String64_3;
    if (m_fields & e_FieldString64_4)
        dup.m_String64_4 = m_String64_4;
    if (m_fields & e_FieldString64_5)
        dup.m_String64_5 = m_String64_5;
    if (m_fields & e_FieldString64_6)
        dup.m_String64_6 = m_String64_6;
    if (m_fields & e_FieldIString64_1)
        dup.m_IString64_1 = m_IString64_1;
    if (m_fields & e_FieldIString64_2)
        dup.m_IString64_2 = m_IString64_2;
    if (m_fields & e_FieldText_1)
        dup.m_Text_1 = m_Text_1;
    if (m_fields & e_FieldText_2)
        dup.m_Text_2 = m_Text_2;
    if (m_fields & e_FieldBlob_1)
        dup.m_Blob_1 = m_Blob_1.copy();
    if (m_fields & e_FieldBlob_2)
        dup.m_Blob_2 = m_Blob_2.copy();
    return dup;
}
