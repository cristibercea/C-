#pragma once
#include "repository.h"
class ActiuneUndo {
public:
	/// <summary>
	/// pure virtual method;
	/// does the undo action, specific for the 
	/// inheritor class;
	/// </summary>
	virtual void doUndo() = 0;

	/// <summary>
	/// destructor that will allow destruction
	/// of inherited classes;
	/// </summary>
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Repository& rep;
	Tenant ten;
public:
	UndoAdauga(Repository& r, const Tenant& t) : rep{ r }, ten{ t } {}

	/// <summary>
	/// undo for adding a tenant
	/// </summary>
	void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
private:
	Repository& rep;
	Tenant ten;
public:
	UndoSterge(Repository& r, const Tenant& t) : rep{ r }, ten{ t } {}

	/// <summary>
	/// undo for deleting a tenant
	/// </summary>
	void doUndo() override;
};

class UndoModifica : public ActiuneUndo {
private:
	Repository& rep;
	Tenant ten;
public:
	UndoModifica(Repository& r, const Tenant& t) : rep{ r }, ten{ t } {}

	/// <summary>
	/// undo for editing a tenant
	/// </summary>
	void doUndo() override;
};


