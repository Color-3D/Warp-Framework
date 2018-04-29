//� 2018 NIREX ALL RIGHTS RESERVED

#ifndef _I_CONTROL_H_
#define _I_CONTROL_H_

#include "WCoordinates.h"
#include "WThickness.h"
#include "WBoundary.h"
#include "WRegistry.h"
#include "WMouseArgs.h"

class IControl : public WEntity
{
public:
	virtual WThickness Location(float top, float left, float bottom, float right) = 0;
	virtual WThickness Location(WCoordinates topleft, WCoordinates botright) = 0;
	virtual WThickness Location(WThickness location) = 0;
	
	virtual WThickness RelLocation(float top, float left, float height, float width) = 0;
	virtual WThickness RelLocation(WCoordinates topleft, WCoordinates heightwidth) = 0;
	virtual WThickness RelLocation(WThickness location) = 0;

	// Getters
	virtual WThickness Location(void) const = 0;

	// Location Setters
	virtual WCoordinates Displace(float X, float Y) = 0;
	virtual WCoordinates Displace(WCoordinates XY) = 0;

	// Getters
	virtual WRegistry* ClickRegistery(void) = 0;
	virtual WRegistry* MouseDownRegistery(void) = 0;
	virtual WRegistry* MouseUpRegistery(void) = 0;
	virtual WRegistry* MouseEnterRegistery(void) = 0;
	virtual WRegistry* MouseLeaveRegistery(void) = 0;

	// Setters
	virtual WRegistry* ClickRegistery(WRegistry* intake) = 0;
	virtual WRegistry* MouseDownRegistery(WRegistry* intake) = 0;
	virtual WRegistry* MouseUpRegistery(WRegistry* intake) = 0;
	virtual WRegistry* MouseEnterRegistery(WRegistry* intake) = 0;
	virtual WRegistry* MouseLeaveRegistery(WRegistry* intake) = 0;

	// Getters
	virtual bool IsEnabled(void) const = 0;
	virtual bool IsVisible(void) const = 0;

	// Setters
	virtual bool IsEnabled(bool input) = 0;
	virtual bool IsVisible(bool input) = 0;

	// Events
	virtual void Click(WMouseArgs* Args) = 0;
	virtual void MouseDown(WMouseArgs* Args) = 0;
	virtual void MouseUp(WMouseArgs* Args) = 0;
	virtual void MouseEnter(WMouseArgs* Args) = 0;
	virtual void MouseLeave(WMouseArgs* Args) = 0;
};

#endif // !_I_CONTROL_H_