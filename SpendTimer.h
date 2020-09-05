/*
 * SpendTimer.h
 *
 *  Created on: 2020-9-5
 *      Author: erices
 */

#pragma once
#ifndef _UTILITIES_SPENDTIMER_H_
#define _UTILITIES_SPENDTIMER_H_

#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fmt/format.h>


namespace util {

/**
 * @ingroup Utilities
 * @addtogroup SpendTimer Spend timer 耗时统计
 * @details 辅助统计代码块执行时间相关的工具宏，编译时可通过指定宏 YIHUA_CLOSE_SPEND_TIME=1
 * 进行关闭，或 YIHUA_CLOSE_SPEND_TIME=0 开启耗时统计
 * @code
 *     {
 *        SPEND_TIME(test, "run test");
 *        ...
 *     }
 * @endcode
 * @{
 */
#if HIKYUU_CLOSE_SPEND_TIME
#define SPEND_TIME(id)
#define SPEND_TIME_MSG(id, ...)
#define close_spend_time()
#define open_spend_time()
#define SPEND_TIMG_CONTROL(open)

#else /* #if HIKYUU_CLOSE_SPEND_TIME */
/**
 * 代码执行耗时计时器
 * @param id 自定义耗时计时器id
 */
#define SPEND_TIME(id)                                                    \
    std::stringstream sptmsg_buf_##id(std::stringstream::out);            \
    sptmsg_buf_##id << #id << " (" << __FILE__ << ":" << __LINE__ << ")"; \
    util::SpendTimer test_spend_timer_##id(sptmsg_buf_##id.str());

/**
 * 代码执行耗时计时器，附带输出信息
 * @param id 自定义耗时计时器id
 * @param ... 符合 fmt::format 方式的输出信息
 */
#define SPEND_TIME_MSG(id, ...)                      \
    std::string msg_##id = fmt::format(__VA_ARGS__); \
    util::SpendTimer test_spend_timer_##id(           \
      fmt::format("{} {} ({}:{})", #id, msg_##id, __FILE__, __LINE__)); 

/**
 * 用于动态控制当前代码块及其子块中的耗时计时器，主要用于测试代码中关闭和开启部分耗时统计
 */
#define SPEND_TIMG_CONTROL(open) util::SpendTimerGuad spend_timer_guard_##open(open);
            

/** @} */

/**
 * 程序执行耗时统计计时器，辅助计算代码执行时间
 * @note 不建议直接使用，应使用相关工具宏
 * @see SPEND_TIME, SPEND_TIME_MSG, SPEND_TIMG_CONTROL
 */
class SpendTimer {
public:
    /** 构造函数，记录当前系统时间 */
    explicit SpendTimer() : m_msg(""), m_start_time(std::chrono::steady_clock::now()) {}

    /**
     * 构造函数，记录当前系统时间
     * @param msg 辅导输出信息
     */
    explicit SpendTimer(const std::string& msg)
    : m_msg(msg), m_start_time(std::chrono::steady_clock::now()) {}

    /** 析构函数，计算从构造至析构所消耗的时间，并打印输出 */
    virtual ~SpendTimer() {
        if (m_closed) {
            return;
        }
        std::chrono::duration<double> sec = std::chrono::steady_clock::now() - m_start_time;
        double spend = 0;
        std::string unit;
        if (sec.count() < 0.000001) {
            spend = sec.count() * 1000000000;
            unit = "ns";
        } else if (sec.count() < 0.001) {
            spend = sec.count() * 1000000;
            unit = "us";
        } else if (sec.count() < 1) {
            spend = sec.count() * 1000;
            unit = "ms";
        } else if (sec.count() > 60) {
            spend = sec.count() / 60;
            unit = " m";
        } else if (sec.count() > 86400) {
            spend = sec.count() / 360;
            unit = " h";
        } else {
            spend = sec.count();
            unit = " s";
        }

        std::cout << fmt::format("spend time: {:>7.3f} {} | {} ", spend, unit, m_msg) << std::endl;
    }

private:
    std::string m_msg;
    std::chrono::time_point<std::chrono::steady_clock> m_start_time;

    static bool m_closed;
    friend void close_spend_time();
    friend void open_spend_time();
};

/** 全局关闭耗时打印输出 */
void close_spend_time();

/** 全局开启耗时打印输出 */
void open_spend_time();

inline void close_spend_time() {
    SpendTimer::m_closed = true;
}

inline void open_spend_time() {
    SpendTimer::m_closed = false;
}

/**
 * 耗时计时器开启关闭状态看守，记录之前的耗时开关状态，并置为指定状态，释放时恢复原状态
 */
class SpendTimerGuad {
public:
    /**
     * 构造函数，记录当前状态，并根据 open 指示开启或关闭耗时统计
     * @param open 是否开启耗时统计
     */
    explicit SpendTimerGuad(bool open) : m_open(open) {
        if (open) {
            open_spend_time();
        } else {
            close_spend_time();
        }
    }

    /** 析构函数，退出当前指定状态，恢复原状态 */
    ~SpendTimerGuad() {
        if (m_open) {
            close_spend_time();
        } else {
            open_spend_time();
        }
    }

private:
    bool m_open;
};

#endif /* HIKYUU_CLOSE_SPEND_TIME */

} /* namespace util */


#endif /* _UTILITIES_SPENDTIMER_H_ */