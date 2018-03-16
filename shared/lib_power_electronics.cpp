#include "lib_power_electronics.h"

double BatteryBidirectionalInverter::convert_to_dc(double P_ac, double * P_dc)
{
	double P_loss = P_ac * (1 - _ac_dc_efficiency);
	*P_dc = P_ac * _ac_dc_efficiency;
	return P_loss;
}
double BatteryBidirectionalInverter::convert_to_ac(double P_dc, double * P_ac)
{
	double P_loss = P_dc * (1 - _dc_ac_efficiency);
	*P_ac = P_dc * _dc_ac_efficiency;
	return P_loss;
}
double BatteryBidirectionalInverter::compute_dc_from_ac(double P_ac)
{
	return P_ac / _dc_ac_efficiency;
}

double BatteryRectifier::convert_to_dc(double P_ac, double * P_dc)
{
	double P_loss = P_ac * (1 - _ac_dc_efficiency);
	*P_dc = P_ac * _ac_dc_efficiency;
	return P_loss;
}

ChargeController::ChargeController(dispatch_t * dispatch, battery_metrics_t * battery_metrics)
{
	m_batteryMetrics = battery_metrics;
	m_dispatch = dispatch;

	if (dynamic_cast<dispatch_manual_front_of_meter_t*>(m_dispatch)) {
		std::unique_ptr<dispatch_t> tmp(new dispatch_manual_front_of_meter_t(*dispatch));
		m_dispatchInitial = std::move(tmp);
	}
	if (dynamic_cast<dispatch_manual_t*>(m_dispatch)) {
		std::unique_ptr<dispatch_t> tmp2(new dispatch_manual_t(*dispatch));
		m_dispatchInitial = std::move(tmp2);
	}
	if (dynamic_cast<dispatch_automatic_behind_the_meter_t*>(m_dispatch)) {
		std::unique_ptr<dispatch_t> tmp3(new dispatch_automatic_behind_the_meter_t(*dispatch));
		m_dispatchInitial = std::move(tmp3);
	}
	if (dynamic_cast<dispatch_automatic_front_of_meter_t*>(m_dispatch)) {
		std::unique_ptr<dispatch_t> tmp4(new dispatch_automatic_front_of_meter_t(*dispatch));
		m_dispatchInitial = std::move(tmp4);
	}
}

ACBatteryController::ACBatteryController(dispatch_t * dispatch, battery_metrics_t * battery_metrics, double efficiencyACToDC, double efficiencyDCToAC) : ChargeController(dispatch, battery_metrics)
{
	std::unique_ptr<BatteryBidirectionalInverter> tmp(new BatteryBidirectionalInverter(efficiencyACToDC, efficiencyDCToAC));
	m_bidirectionalInverter = std::move(tmp);
	m_batteryPower = dispatch->getBatteryPower();
	m_batteryPower->connectionMode = ChargeController::AC_CONNECTED;
	m_batteryPower->singlePointEfficiencyACToDC = m_bidirectionalInverter->ac_dc_efficiency();
	m_batteryPower->singlePointEfficiencyDCToDC = m_bidirectionalInverter->dc_ac_efficiency();
}

void ACBatteryController::run(size_t year, size_t hour_of_year, size_t step_of_hour, size_t index, double P_pv, double P_load)
{
	if (P_pv < 0)
	{
		m_batteryPower->powerPVInverterDraw = P_pv;
		m_batteryPower->powerPV = 0;
		P_pv = 0;
	}
	m_dispatch->dispatch(year, hour_of_year, step_of_hour, P_pv, P_pv, P_load, P_load, 0);

}