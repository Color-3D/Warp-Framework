// � 2019 NIREX ALL RIGHTS RESERVED

#ifndef _W_SMOOTHSTEP_H_
#define _W_SMOOTHSTEP_H_

#include "WEntity.h"
#include "WSmoothStepArgs.h"
#include "WMath.h"
#include "WRegistry.h"
#include "WDefines.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <future>
#include <memory>

//-->DOC_CLASS
// A Class for performing a smooth step transformation between two numbers
class WSmoothStep : public WEntity
{
public:
	//-->DOC_FUNC
	// Initialize all the required values to perform a smooth step transformation
	// From: color value to begin with
	// To: target color value
	// Delay: Delay between each LERP epoch
	WSmoothStep(W_FLOAT from, W_FLOAT to, W_LONG delay = 1);
	~WSmoothStep(void);

	WRegistry* TickRegistry(void) const;
	WRegistry* DoneRegistry(void) const;

	W_LONG Delay(void) const;
	W_FLOAT Value(void) const;
	W_FLOAT From(void) const;
	W_FLOAT To(void) const;

	//-->DOC_FUNC
	// Function to determine whether or not the Transformation is being performed
	// Returns: True if in transform, False if transform is finished. 
	bool IsRunning(void);

	WRegistry* TickRegistry(WRegistry* intake);
	WRegistry* DoneRegistry(WRegistry* intake);

	W_LONG Delay(W_LONG intake);
	W_FLOAT Value(W_FLOAT intake);
	W_FLOAT From(W_FLOAT intake);
	W_FLOAT To(W_FLOAT intake);

	//-->DOC_FUNC
	// Begin Transformation (no safeguards)
	void Perform(void);

	//-->DOC_FUNC
	// Begin Transformation (with safeguards)
	void PerformSafe(void);

	//-->DOC_FUNC
	// Stop Transformation if it's already happening
	void Stop(void);

private:
	void WorkerWork(void);
	bool WorkThread(std::thread& out);

private:
	//-->DOC_MEMBER
	// Delay Between each epoch
	W_LONG m_delay;

	//-->DOC_MEMBER
	// Current Value of the smooth step
	W_FLOAT m_value;

	//-->DOC_MEMBER
	// Value to begin with
	W_FLOAT m_from;

	//-->DOC_MEMBER
	// Target value to get close to
	W_FLOAT m_to;

	std::thread* thr;
	std::mutex m_MutexLock;

	bool m_stop;
	bool m_isRunning;

	//-->DOC_MEMBER
	// Function registry that is called on each Tick
	WRegistry* m_SmoothStepTickRegistry;

	//-->DOC_MEMBER
	// Function registry that is called when transformation is finished
	WRegistry* m_SmoothStepDoneRegistry;
};

#endif // !_W_SMOOTHSTEP_H_
