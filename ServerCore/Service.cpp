#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "Listener.h"

/*-------------
	Service
--------------*/

Service::Service(ServiceType type, NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: _type(type), _netAddress(address), _iocpCore(core), _sessionFactory(factory), _maxSessionCount(maxSessionCount)
{

}

Service::~Service()
{
}

void Service::CloseService()
{
	// TODO
}

SessionRef Service::CreateSession()
{
	SessionRef session = _sessionFactory();
	session->SetService(shared_from_this());

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Service::AddSession(SessionRef session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void Service::ReleaseSession(SessionRef session)
{
	WRITE_LOCK;
	ASSERT_CRASH(_sessions.erase(session) != 0);
	_sessionCount--;
}

/*-----------------
	ClientService
------------------*/

ClientService::ClientService(NetAddress targetAddress, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: Service(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	cout << "Connect to Server . . ." << endl;

	if (CanStart() == false) {
		cout << "CLIENT CANSTART ERROR" << endl;
		return false;
	}

	const int32 sessionCount = GetMaxSessionCount();
	for (int32 i = 0; i < sessionCount; i++)
	{
		SessionRef session = CreateSession();
		if (session->Connect() == false) {
			cout << "CLIENT CONNECT ERROR" << endl;
			return false;
		}
	}
	
	
	return true;
}


/*-----------------
	ServerService
------------------*/
ServerService::ServerService(NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: Service(ServiceType::Server, address, core, factory, maxSessionCount)
{
}

bool ServerService::Start()
{
	cout << "Server Starting . . ." << endl;


	if (CanStart() == false) {
		cout << "SERVER CANSTART ERROR" << endl;
		return false;
	}

	_listener = MakeShared<Listener>();
	if (_listener == nullptr) {
		cout << "LISTENER NULL POINT ERROR" << endl;
		return false;
	}

	ServerServiceRef service = static_pointer_cast<ServerService>(shared_from_this());
	if (_listener->StartAccept(service) == false) {
		cout << "START ACCEPT ERROR" << endl;
		return false;
	}

	cout << "Server Start!" << endl;

	return true;
}

void ServerService::CloseService()
{
	// TODO

	Service::CloseService();
}
