static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         ProsilicaCCD.cpp
//
// description :  C++ source for the ProsilicaCCD and its commands.
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                ProsilicaCCD are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
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
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name|  Method name
//	----------------------------------------
//  State  |  dev_state()
//
//===================================================================


#include <ProsilicaCCD.h>
#include <ProsilicaCCDClass.h>
#include <tango.h>
#include <PogoHelper.h>
namespace ProsilicaCCD_ns
{

//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::ProsilicaCCD(string &s)
//
// description :     constructor for simulated ProsilicaCCD
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------
ProsilicaCCD::ProsilicaCCD(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
    init_device();
}

ProsilicaCCD::ProsilicaCCD(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
    init_device();
}

ProsilicaCCD::ProsilicaCCD(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
    init_device();
}
//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::delete_device()
//
// description :     will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void ProsilicaCCD::delete_device()
{
    INFO_STREAM << "ProsilicaCCD::ProsilicaCCD() delete device " << device_name << endl;	
    //    Delete device allocated objects

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("ProsilicaCCD");
    //    m_ct = 0;
    //}
}

//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::init_device()
//
// description :     will be called at device initialization.
//
//-----------------------------------------------------------------------------
void ProsilicaCCD::init_device()
{
    INFO_STREAM << "ProsilicaCCD::ProsilicaCCD() create device " << device_name << endl;

    // Initialise variables to default values
    //--------------------------------------------
    get_device_property();
    m_is_device_initialized = false;
    set_state(Tango::INIT);
    m_status_message.str("");

    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object, no need to give it the ip !!
        m_ct = ControlFactory::instance().get_control("ProsilicaCCD");

        //- get interface to specific camera
        m_hw = dynamic_cast<Prosilica::Interface*>(m_ct->hwInterface());
        if(m_hw==0)
        {
            INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"ProsilicaCCD"<<") !"<< endl;
            m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"ProsilicaCCD"<<") !"<< endl;
            m_is_device_initialized = false;
            set_state(Tango::INIT);
            return;
        }
	
    }
    catch(Exception& e)
    {
        INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
        m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
        m_is_device_initialized = false;
        set_state(Tango::INIT);
        return;
    }
    catch(...)
    {
        INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
        m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
        set_state(Tango::INIT);
        m_is_device_initialized = false;
        return;
    }
    m_is_device_initialized = true;
    set_state(Tango::STANDBY);
    this->dev_state();
}


//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::get_device_property()
//
// description :     Read the device properties from database.
//
//-----------------------------------------------------------------------------
void ProsilicaCCD::get_device_property()
{
    //    Initialize your default values here (if not done with  POGO).
    //------------------------------------------------------------------

    //    Read device properties from database.(Automatic code generation)
    //------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorIP"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	ProsilicaCCDClass	*ds_class =
		(static_cast<ProsilicaCCDClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorIP from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorIP;
	else {
		//	Try to initialize DetectorIP from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorIP;
	}
	//	And try to extract DetectorIP value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorIP;



    //    End of Automatic code generation
    //------------------------------------------------------------------
    create_property_if_empty(dev_prop,"127.0.0.1","DetectorIP");
	
}
//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::always_executed_hook()
//
// description :     method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void ProsilicaCCD::always_executed_hook()
{
	DEBUG_STREAM << "ProsilicaCCD::always_executed_hook() entering... "<< endl;
	try
	{
		//- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("ProsilicaCCD");

		//- get interface to specific detector
		if(m_ct!=0)
			m_hw = dynamic_cast<Prosilica::Interface*>(m_ct->hwInterface());

	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
		//- throw exception
		set_state(Tango::INIT);
		m_is_device_initialized = false;
		return;
	}
	catch(...)
	{
		ERROR_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		//- throw exception
		set_state(Tango::INIT);
		m_is_device_initialized = false;
		return;
	}
}


//+----------------------------------------------------------------------------
//
// method :         ProsilicaCCD::read_attr_hardware
//
// description :     Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void ProsilicaCCD::read_attr_hardware(vector<long> &attr_list)
{
    DEBUG_STREAM << "ProsilicaCCD::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
    //    Add your own code here
}

//+------------------------------------------------------------------
/**
 *    method:    ProsilicaCCD::dev_state
 *
 *    description:    method to execute "State"
 *    This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return    State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState ProsilicaCCD::dev_state()
{
    Tango::DevState    argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "ProsilicaCCD::dev_state(): entering... !" << endl;
    
    
    //    Add your own code to control device here

    stringstream    DeviceStatus;
    DeviceStatus     << "";
    Tango::DevState DeviceState    = Tango::STANDBY;
    if(!m_is_device_initialized )
    {
        DeviceState            = Tango::INIT;
        DeviceStatus        << m_status_message.str();
    }
    else if (m_ct==0)
    {
        DeviceState            = Tango::INIT;
        DeviceStatus        <<"Initialization Failed : Unable to get the lima control object !\n\n";
    }
    else
    {
    	CtControl::Status status;
		m_ct->getStatus(status);
		if (status.AcquisitionStatus == lima::AcqReady)
		{
			HwInterface::StatusType state;
			m_hw->getStatus(state);
			if(state.acq == AcqRunning && state.det == DetExposure)
			{
				DeviceState=Tango::RUNNING;
				DeviceStatus<<"Acquisition is Running ...\n"<<endl;
			}
			else if(state.acq == AcqFault && state.det == DetFault)
			{
				DeviceState=Tango::INIT;//INIT
				DeviceStatus<<"Acquisition is in Init\n"<<endl;
			}
			else if(state.acq == AcqFault && state.det == DetIdle)
			{
				DeviceState=Tango::FAULT;//FAULT
				DeviceStatus<<"Acquisition is in Fault\n"<<endl;
			}
			else
			{
				DeviceState=Tango::STANDBY;
				DeviceStatus<<"Waiting for Request ...\n"<<endl;
			}
		}
		else if(status.AcquisitionStatus == lima::AcqRunning)
		{
			DeviceState=Tango::RUNNING;
			DeviceStatus<<"Acquisition is Running ...\n"<<endl;
		}
		else
		{
			HwInterface::StatusType state;
			m_hw->getStatus(state);
			if(state.acq == AcqFault && state.det == DetFault)
			{
				DeviceState=Tango::INIT;//INIT
				DeviceStatus<<"Acquisition is in Init\n"<<endl;
			}
			else
			{
			  DeviceState=Tango::FAULT;//FAULT
			  DeviceStatus<<"Acquisition is in Fault\n"<<endl;
			}
		}
    }

    set_state(DeviceState);
    set_status(DeviceStatus.str());

    argout = DeviceState;
    return argout;
}



/*-------------------------------------------------------------------------
//       LimaDetector::store_value_as_property
/-------------------------------------------------------------------------*/
template <class T>
void ProsilicaCCD::store_value_as_property (T value, string property_name)
{
    Tango::DbDatum current_value(property_name);
    current_value << value;
    Tango::DbData db_data;
    db_data.push_back(current_value);
    try
    {
        get_db_device()->put_property(db_data);
    }
    catch(Tango::DevFailed &df)
    {
        string message= "Error in storing " + property_name + " in Configuration DataBase ";
        LOG_ERROR((message));
        ERROR_STREAM<<df<<endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("LimaDetector::store_value_as_property"));
    }

}

/*-------------------------------------------------------------------------
//       LimaDetector::create_property_if_empty
/-------------------------------------------------------------------------*/
template <class T>
void ProsilicaCCD::create_property_if_empty(Tango::DbData& dev_prop,T value,string property_name)
{
    int iPropertyIndex = FindIndexFromPropertyName(dev_prop,property_name);
    if (iPropertyIndex == -1) return;
    if (dev_prop[iPropertyIndex].is_empty())
    {
        Tango::DbDatum current_value(dev_prop[iPropertyIndex].name);
        current_value << value;
        Tango::DbData db_data;
        db_data.push_back(current_value);

        try
        {
            get_db_device()->put_property(db_data);
        }
        catch(Tango::DevFailed &df)
        {
            string message= "Error in storing " + property_name + " in Configuration DataBase ";
            LOG_ERROR((message));
            ERROR_STREAM<<df<<endl;
            //- rethrow exception
            Tango::Except::re_throw_exception(df,
                        static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                        static_cast<const char*> (string(df.errors[0].desc).c_str()),
                        static_cast<const char*> ("LimaDetector::create_property_if_empty"));
        }
    }
}


/*-------------------------------------------------------------------------
//       LimaDetector::FindIndexFromPropertyName
/-------------------------------------------------------------------------*/
int ProsilicaCCD::FindIndexFromPropertyName(Tango::DbData& dev_prop, string property_name)
{
    size_t iNbProperties = dev_prop.size();
    unsigned int i;
    for (i=0;i<iNbProperties;i++)
    {
        string sPropertyName(dev_prop[i].name);
        if (sPropertyName == property_name) return i;
    }
    if (i == iNbProperties) return -1;
    return i;
}

}	//	namespace

