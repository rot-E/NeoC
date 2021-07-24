#include "Derived.h"

static void _Setup() {
	Derived._Initialised = true;
	Derived.GetNum = Base.GetNum;
}

static void AddNum(self_t *der, const int32_t num) {
	act(Base_t, der)->_Num += num;
}

static Derived_t *Init(Derived_t *der) {
	// 生成・継承時に最初に呼び出されるのはこのメソッドであるため↓
	if (!Derived._Initialised) Derived._Setup();

	Base.Init(act(Base_t, der));
	// 基底クラスのフィールド・メソッド変更等
	//

	// フィールドの初期化: 基底クラスのフィールドも上書き可能
	//

	// メソッドの設定: 函数ポインタの上書きでoverride可能
	der->GetNum = Base.GetNum;
				// 可能: act(Base_t, der)->GetNum;
	der->AddNum = AddNum;

	return der;
}

static Derived_t *New() {
	return Derived.Init(new (Derived_t));
}

static void Delete(Derived_t *der) {
	delete (der);
}

_Derived Derived = {
	._Initialised	= false,
	._Setup			= _Setup,

	.Init			= Init,
	.New			= New,
	.Delete			= Delete,

	.AddNum			= AddNum,
};
