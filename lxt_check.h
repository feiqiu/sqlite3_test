#ifndef _LXT_CHECK_H_
#define _LXT_CHECK_H_

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

//PTR
#define  CHECK_PtrRetBool(x) 			if (x == NULL){LOG_Err("%s NULL", #x); return false;}

#define  CHECK_PtrRetInt(x) 			if (x == NULL){LOG_Err("%s NULL", #x); return -1;}

#define  CHECK_PtrGoEnd(x) 				if (x == NULL){LOG_Err("%s NULL", #x); goto end;}

#define  CHECK_PtrRetVoid(x) 			if (x == NULL){LOG_Err("%s NULL", #x);return;}

#define  CHECK_PtrRetPtr(x) 			if (x == NULL){LOG_Err("%s NULL", #x);return NULL;}

#define  CHECK_PtrQuietRet(x) 			if (x == NULL){return NULL;}

//BOOL
#define  CHECK_TrueRetBool(x) 			if (!x){LOG_Err("%s false", #x); return false;}

#define  CHECK_TrueRetInt(x) 			if (!x){LOG_Err("%s false", #x); return -1;}

#define  CHECK_TrueGoEnd(x) 			if (!x){LOG_Err("%s false", #x); goto end;}

#define  CHECK_TrueRetVoid(x) 			if (!x){LOG_Err("%s false", #x); return;}

#define  CHECK_TrueQuietRetPtr(x) 		if (!x){return NULL;}

//<
#define  CHECK_LTRetBool(x, y) 			if (x >= y)	{LOG_Err("%s<%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return false;}

#define  CHECK_LTRetInt(x, y) 			if (x >= y)	{LOG_Err("%s<%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return -1;}

#define  CHECK_LTGoEnd(x, y) 			if (x >= y)	{LOG_Err("%s<%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); goto end;}

#define  CHECK_LTRetVoid(x, y) 			if (x >= y)	{LOG_Err("%s<%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return;}

// <=
#define  CHECK_LERetBool(x, y) 			if (x > y)	{LOG_Err("%s<=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return false;}

#define  CHECK_LERetInt(x, y) 			if (x > y)	{LOG_Err("%s<=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return -1;}

#define  CHECK_LEGoEnd(x, y) 			if (x > y)	{LOG_Err("%s<=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); goto end;}

#define  CHECK_LERetVoid(x, y) 			if (x > y)	{LOG_Err("%s<=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return;}

#define  CHECK_LERetPtr(x, y) 			if (x > y)	{LOG_Err("%s<=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return NULL;}

// ==
#define  CHECK_EQRetBool(x, y) 			if (x != y)	{LOG_Err("%s==%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return false;}

#define  CHECK_EQRetInt(x, y) 			if (x != y)	{LOG_Err("%s==%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return -1;}

#define  CHECK_EQGoEnd(x, y)	 		if (x != y) {LOG_Err("%s==%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); goto end;}

#define  CHECK_EQRetVoid(x, y)	 		if (x != y) {LOG_Err("%s==%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return;}

// >
#define  CHECK_GTRetBool(x, y)			if (x <= y) {LOG_Err("%s>%s error,%s:%d,%s:%d,%s", #x, #y, #x, x, #y, y); return false;}

#define  CHECK_GTRetInt(x, y) 			if (x <= y)	{LOG_Err("%s>%s error,%s:%d,%s:%d,%s", #x, #y, #x, x, #y, y); return -1;}

#define  CHECK_GTGoEnd(x, y) 			if (x <= y)	{LOG_Err("%s>%s error,%s:%d,%s:%d,%s", #x, #y, #x, x, #y, y); goto end;}

#define  CHECK_GTRetVoid(x, y) 			if (x <= y)	{LOG_Err("%s>%s error,%s:%d,%s:%d,%s", #x, #y, #x, x, #y, y); return;}

// >=
#define  CHECK_GERetBool(x, y) 			if (x < y)	{LOG_Err("%s>=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return false;}

#define  CHECK_GERetInt(x, y) 			if (x < y)  {LOG_Err("%s>=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return -1;}

#define  CHECK_GEGoEnd(x, y) 			if (x < y)  {LOG_Err("%s>=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); goto end;}

#define  CHECK_GERetVoid(x, y) 			if (x < y)  {LOG_Err("%s>=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return;}

#define  CHECK_GERetPtr(x, y) 			if (x < y)  {LOG_Err("%s>=%s error,%s:%d,%s:%d", #x, #y, #x, x, #y, y); return NULL;}

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
