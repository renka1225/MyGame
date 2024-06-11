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
	obj2.AddComponent<Pos>();

    // GetComponent
    std::cout << "[GetComponent:]" << std::endl;
    auto temp1 = obj1.GetComponent<UI>();
    temp1.ShowComponentName();
    auto temp2 = obj2.GetComponent<Text>();
    temp2.ShowComponentName();
    auto temp3 = obj2.GetComponent<Pos>();
    temp3.ShowComponentName();

    //obj1.GetComponent<UI>()->ShowComponentName();
    //obj2.GetComponent<Text>()->ShowComponentName();
    //obj2.GetComponent<Pos>()->ShowComponentName();

    //// DelComponent
    //obj2.DelComponent<Pos>();

    //// 確認
    //std::cout << "[全体の確認:]" << std::endl;
    //obj1.ShowComponents();
    //obj2.ShowComponents();

	return 0;
}