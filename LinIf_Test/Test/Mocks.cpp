/*
 * Mocks.cpp
 *
 *  Created on: 19 Mar 2019
 *      Author: messam
 */

#ifndef TEST_MOCKS_CPP_
#define TEST_MOCKS_CPP_

#include "Mocks.h"
#include "PduR.h"
#include "Lin.h"
#include <memory>

extern std::shared_ptr<PduRMock> PdurMockPtr;
extern std::shared_ptr<LinMock> LinMockPtr;
extern std::shared_ptr<LinSMMock> LinSMMockPtr;

Std_ReturnType PduR::PduR::LinIfTriggerTransmit(PduIdType TxPduId, PduInfoType& PduInfoPtr){
	for(auto i = 0U; i < PduInfoPtr.PduPtr.size(); i++){
		PduInfoPtr.PduPtr[i] = 250;
	}

	return PdurMockPtr->LinIfTriggerTransmit(TxPduId, PduInfoPtr.PduPtr);
}

void PduR::PduR::LinIfTxConfirmation(PduIdType TxPduId, Std_ReturnType result){
	PdurMockPtr->LinIfTxConfirmation(TxPduId, result);
}

void PduR::PduR::LinIfRxIndication(PduIdType RxPduId, const PduInfoType& PduInfoPtr){
	PdurMockPtr->LinIfRxIndication(RxPduId, PduInfoPtr.PduPtr);
}

Std_ReturnType Lin::Lin::SendFrame(uint8 Channel, const Lin_PduType* PduInfoPtr){
	return LinMockPtr->SendFrame(Channel, PduInfoPtr->SduPtr);
}

Lin::Lin_StatusType Lin::Lin::GetStatus(uint8 Channel, uint8** Lin_SduPtr){
	return LinMockPtr->GetStatus(Channel, Lin_SduPtr);
}

Std_ReturnType Lin::Lin::GoToSleep(uint8 Channel){
	return LinMockPtr->GoToSleep(Channel);
}

Std_ReturnType Lin::Lin::GoToSleepInternal(uint8 Channel){
	return LinMockPtr->GoToSleepInternal(Channel);
}

void LinSM::LinSM::ScheduleRequestConfirmation(NetworkHandleType network, LinIf::LinIf_SchHandleType ScheduleId){
	LinSMMockPtr->ScheduleRequestConfirmation(network, ScheduleId);
}

void LinSM::LinSM::WakeupConfirmation(NetworkHandleType network, bool success){
	LinSMMockPtr->WakeupConfirmation(network, success);
}

void LinSM::LinSM::GotoSleepConfirmation(NetworkHandleType network, bool success){
	LinSMMockPtr->GotoSleepConfirmation(network, success);
}

#endif /* TEST_MOCKS_CPP_ */
