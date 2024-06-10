#include <iostream>
#include "GameObject.h"
#include "UI.h"
#include "Text.h"
#include "Pos.h"

int main()
{
	GameObject obj1;
	GameObject obj2;

	// AddComponent
	obj1.AddComponent<UI>();
	obj2.AddComponent<Text>();
	obj2.AddComponent<Text>();

	// GetComponent
	UI temp1 = obj1.GetComponent<UI>();
	temp1.ShowComponentName();
	UI temp2 = obj2.GetComponent<UI>();
	temp2.ShowComponentName();
	UI temp3 = obj2.GetComponent<UI>();
	temp3.ShowComponentName();

	return 0;
}