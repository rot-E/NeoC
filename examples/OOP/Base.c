#include "Base.h"

static int32_t GetNum(self_t *base) {
	return act(Base_t, base)->_Num;
}

static Base_t *Init(Base_t *base) {
	// フィールドの初期化
	base->_Num = 3;

	// メソッドの設定
	base->GetNum = GetNum;

	return base;
}

static Base_t *New() {
	return Base.Init(new(Base_t));
}

static void Delete(Base_t *base) {
	delete(base);
}

_Base Base = {
	.Init		= Init,
	.New		= New,
	.Delete		= Delete,

	.GetNum		= GetNum,
};
