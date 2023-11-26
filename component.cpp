#include "main.h"
#include "renderer.h"
#include "component.h"
#include "gameObject.h"




void Component::Destroy()
{
	Uninit();
	delete this;
}



