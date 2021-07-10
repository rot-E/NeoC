#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"
#include "NeoC/System.h"

void main() $NeoC {
   String_t *text = String.New("NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   try {
      int32_t fi = String.FirstIndexOf(text, 'i');
      int32_t li = String.LastIndexOf(text, 'i');

      for (int32_t i = 0; i < String.GetLength(text); i++) {
         Console.WriteChar((i == fi || i == li)? '^' : ' ');
		 System.USleep(50 * 1000);
      }
      Console.NewLine();

   } catch (String.RuntimeException) {
      Console.WriteErrorLine(String.New("[Error] Target Not Found."));
   } end

} NeoC$
