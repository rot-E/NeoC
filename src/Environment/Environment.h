#pragma once

/* ------------------------------------------------------ */
/* 環境開始宣言 */
#define $_ { _S._Setup(); E.Try(({ void Try() {

/* 環境終了宣言 */
#define _$ }; Try; }), ({ void Catch() { _S._HANDLER(); }; Catch; }), ({ void Finally() {}; Finally; })); }


/* 可変長引数使用開始宣言 */
#define use(FMT_STR) va_list ap; va_start(ap, FMT_STR);

/* 可変長引数使用終了宣言 */
#define release va_end(ap);
/* ------------------------------------------------------ */
