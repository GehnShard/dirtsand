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

#ifndef _MOUL_BULLETMSG_H
#define _MOUL_BULLETMSG_H

#include "Message.h"
#include "Types/Math.h"

namespace MOUL
{
    class BulletMsg : public Message
    {
        FACTORY_CREATABLE(BulletMsg)

        void read(DS::Stream* stream) override;
        void write(DS::Stream* stream) const override;

    public:
        enum { e_Stop, e_Shot, e_Spray };

        uint8_t m_cmd;
        DS::Vector3 m_from, m_direction;
        float m_range, m_radius, m_partyTime;

    protected:
        BulletMsg(uint16_t type)
            : Message(type), m_cmd(), m_range(), m_radius(), m_partyTime() { }
    };
};

#endif // _MOUL_BULLETMSG_H
