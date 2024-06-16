#include "undo.h"

void UndoAdauga::doUndo() {
	rep.destroy(ten.get_name());
}

void UndoSterge::doUndo() {
	rep.store(ten);
}

void UndoModifica::doUndo() {
	rep.edit(ten);
}
