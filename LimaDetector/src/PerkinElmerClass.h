//=============================================================================
//
// file :         PerkinElmerClass.h
//
// description :  Include for the PerkinElmerClass root class.
//                This class is the singleton class for
//                the PerkinElmer device class.
//                It contains all properties and methods which the 
//                PerkinElmer requires only once e.g. the commands.
//			
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :     European Synchrotron Radiation Facility
//                BP 220, Grenoble 38043
//                FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#ifndef _PERKINELMERCLASS_H
#define _PERKINELMERCLASS_H

#include <tango.h>
#include <PerkinElmer.h>


namespace PerkinElmer_ns
{//=====================================
//	Define classes for attributes
//=====================================
class gainAttrib: public Tango::Attr
{
public:
	gainAttrib():Attr("gain", Tango::DEV_LONG, Tango::READ_WRITE) {};
	~gainAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<PerkinElmer *>(dev))->read_gain(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<PerkinElmer *>(dev))->write_gain(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<PerkinElmer *>(dev))->is_gain_allowed(ty);}
};

class keepFirstImageAttrib: public Tango::Attr
{
public:
	keepFirstImageAttrib():Attr("keepFirstImage", Tango::DEV_BOOLEAN, Tango::READ_WRITE) {};
	~keepFirstImageAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<PerkinElmer *>(dev))->read_keepFirstImage(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<PerkinElmer *>(dev))->write_keepFirstImage(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<PerkinElmer *>(dev))->is_keepFirstImage_allowed(ty);}
};

class correctionModeAttrib: public Tango::Attr
{
public:
	correctionModeAttrib():Attr("correctionMode", Tango::DEV_STRING, Tango::READ_WRITE) {};
	~correctionModeAttrib() {};
	
	virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
	{(static_cast<PerkinElmer *>(dev))->read_correctionMode(att);}
	virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
	{(static_cast<PerkinElmer *>(dev))->write_correctionMode(att);}
	virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
	{return (static_cast<PerkinElmer *>(dev))->is_correctionMode_allowed(ty);}
};

//=========================================
//	Define classes for commands
//=========================================
class StartAcqGainImageCmd : public Tango::Command
{
public:
	StartAcqGainImageCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StartAcqGainImageCmd(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StartAcqGainImageCmd() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PerkinElmer *>(dev))->is_StartAcqGainImage_allowed(any);}
};



class StartAcqOffsetImageClass : public Tango::Command
{
public:
	StartAcqOffsetImageClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out,
				   const char        *in_desc,
				   const char        *out_desc,
				   Tango::DispLevel  level)
	:Command(name,in,out,in_desc,out_desc, level)	{};

	StartAcqOffsetImageClass(const char   *name,
	               Tango::CmdArgType in,
				   Tango::CmdArgType out)
	:Command(name,in,out)	{};
	~StartAcqOffsetImageClass() {};
	
	virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
	virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
	{return (static_cast<PerkinElmer *>(dev))->is_StartAcqOffsetImage_allowed(any);}
};



//
// The PerkinElmerClass singleton definition
//

class
#ifdef WIN32
	__declspec(dllexport)
#endif
	PerkinElmerClass : public Tango::DeviceClass
{
public:
//	properties member data

//	add your own data members here
//------------------------------------

public:
	Tango::DbData	cl_prop;
	Tango::DbData	cl_def_prop;
	Tango::DbData	dev_def_prop;

//	Method prototypes
	static PerkinElmerClass *init(const char *);
	static PerkinElmerClass *instance();
	~PerkinElmerClass();
	Tango::DbDatum	get_class_property(string &);
	Tango::DbDatum	get_default_device_property(string &);
	Tango::DbDatum	get_default_class_property(string &);
	
protected:
	PerkinElmerClass(string &);
	static PerkinElmerClass *_instance;
	void command_factory();
	void get_class_property();
	void attribute_factory(vector<Tango::Attr *> &);
	void write_class_property();
	void set_default_property();
	string get_cvstag();
	string get_cvsroot();

private:
	void device_factory(const Tango::DevVarStringArray *);
};


}	//	namespace PerkinElmer_ns

#endif // _PERKINELMERCLASS_H
