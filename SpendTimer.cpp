/*
 * SpendTimer.h
 *
 *  Created on: 2020-9-5
 *      Author: erices
 */

#include "SpendTimer.h"

namespace util {

#if !HIKYUU_CLOSE_SPEND_TIME
bool SpendTimer::m_closed = false;
#endif

} /* namespace util */