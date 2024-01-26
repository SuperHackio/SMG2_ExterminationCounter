#include "kamek/hooks.h"
#include "CollectCounter.h"
#include "Game/LiveActor/LiveActor.h"
#include "Game/Player/MarioActor.h"
#include "Game/Player/Mario.h"
#include "Game/Util/ActorSensorUtil.h"
#include "Game/Util/EventUtil.h"
#include "Game/Util/SceneUtil.h"

// Extermination Counter
// Author: Super Hackio
// Description: That one planet from Space Junk...

void tryTrampleCounter()
{
	register MarioActor* pMarioActor;
	register HitSensor* pSensor;
	__asm
	{
		mr pMarioActor, r31
		mr pSensor, r30
	}

	//We only have one galaxy in this mod. Not very flexible I know...
	if (MR::getCurrentScenarioNo() == 3)
	{
		register LiveActor* pSensorHost = MR::getSensorHost(pSensor);
		if (!strcmp(pSensorHost->mName, "\x83\x4E\x83\x8A\x83\x7B\x81\x5B")) //This string just says Kuribo's Japanese name (the one in the ObjNameTable)
		{
			register u8 ValueA;
			register CollectCounter* pCounter;
			__asm
			{
				lwz pCounter, 0x564(pMarioActor)
				lbz ValueA, 0xE7D(pMarioActor)
			}
			pMarioActor->mMario->playSoundTrampleCombo(ValueA);
			ValueA++;
			if (ValueA > 1 && ValueA < 8)
			{
				pCounter->setCount(ValueA);
			}
			if (ValueA >= 8)
			{
				pCounter->kill();
				ValueA = 7;
				MR::addPlayerLeft(1);
			}
			__asm
			{
				stb ValueA, 0xE7D(pMarioActor)
			}
		}
	}
}

kmCall(0x803D22DC, tryTrampleCounter);

//For some reason the compiler refused to actually put this ASM into the bin
asm void bruh()
{
	lwz r4, 0x590(r31)
	mr r3, r31
}
kmCall(0x803D22E0, bruh);
