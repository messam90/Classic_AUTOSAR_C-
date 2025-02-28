/*
 * Test.cpp
 *
 *  Created on: Mar 24, 2019
 *      Author: m
 */
#include "Mocks.h"
#include "PduR.h"

std::shared_ptr<LinIfMock> LinIfMockPtr;
std::shared_ptr<LdComMock> LdComMockPtr;
std::shared_ptr<PduR::PduR> PduRPtr;
std::shared_ptr<LinIf::LinIf> LinIfPtr;
std::shared_ptr<LdCom::LdCom> LdComPtr;

using ::testing::Return;
using ::testing::_;
using ::testing::SetArrayArgument;
using ::testing::DoAll;

class PDUR: public ::testing::Test{
	void SetUp()override{
		LinIfMockPtr = std::make_shared<LinIfMock>();
		LdComMockPtr = std::make_shared<LdComMock>();
		PduRPtr = std::make_shared<PduR::PduR>();
	}

	void TearDown(){
		LinIfMockPtr.reset();
		LdComMockPtr.reset();
		PduRPtr.reset();
	}
};

PduR::RoutingPathsType Configure(){
	PduR::IFRoutingPathType TxPath(0, 0, PduR::ModulesType::LDCOM, PduR::ModulesType::LINIF);
	PduR::IFRoutingPathType RxPath(0, 0, PduR::ModulesType::LINIF, PduR::ModulesType::LDCOM);

	PduR::RoutingPathsType RoutingPaths;
	RoutingPaths.AddRoutingPath(TxPath, PduR::RoutingDirection::TRANSMIT);
	RoutingPaths.AddRoutingPath(RxPath, PduR::RoutingDirection::RECEIVE);

	return RoutingPaths;
}

TEST_F(PDUR, TRANSMIT){
	PduRPtr->Init(Configure, LinIfPtr, LdComPtr);
	PduIdType PduId = 0;
	std::vector<uint8> Data(8, 1);
	PduInfoType PduInfo{Data, (uint16)Data.size()};
	EXPECT_CALL(*LinIfMockPtr, Transmit(PduId, Data)).WillOnce(Return(Std_ReturnType::E_OK));
	ASSERT_EQ(PduRPtr->LdComTransmit(PduId, PduInfo), Std_ReturnType::E_OK);
}

TEST_F(PDUR, TRIGGER_TRANSMIT){
	PduRPtr->Init(Configure, LinIfPtr, LdComPtr);
	PduIdType PduId = 0;
	std::vector<uint8> Data(8, 1);
	PduInfoType PduInfo{Data, (uint16)Data.size()};
	EXPECT_CALL(*LdComMockPtr, TriggerTransmit(PduId,_)).WillOnce(Return(Std_ReturnType::E_OK));
	ASSERT_EQ(PduRPtr->LinIfTriggerTransmit(PduId, PduInfo), Std_ReturnType::E_OK);
	ASSERT_EQ(Data[1], 250);
}

TEST_F(PDUR, RECEIVE){
	PduRPtr->Init(Configure, LinIfPtr, LdComPtr);
	PduIdType PduId = 0;
	std::vector<uint8> Data(8, 1);
	PduInfoType PduInfo{Data, (uint16)Data.size()};
	EXPECT_CALL(*LdComMockPtr, RxIndication(PduId, Data));
	PduRPtr->LinIfRxIndication(PduId, PduInfo);
}
