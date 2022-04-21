#include "Processor.hpp"

Processor::Processor() :
    m_clock(0),
    m_total_instr(0),
    m_arithmetic_instr(0),
    m_logical_instr(0),
    m_data_instr(0),
    m_control_instr(0),
    m_halt_instr(0),
    m_stall(0),
    m_data_stalls(0),
    m_control_stalls(0)
{}
