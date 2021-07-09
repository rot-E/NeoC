#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"

void main() $NeoC {
   String_t *text = String.New("NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   try {
      int32_t fm = String.FirstIndexOf(text, 'i');
      int32_t lm = String.LastIndexOf(text, 'i');

      for (int32_t i = 0; i < String.GetLength(text); i++) {
         Console.WriteChar((i == fm || i == lm)? '^' : ' ');
      }
      Console.NewLine();

   } catch (String.RuntimeException) {
      Console.WriteErrorLine(String.New("[Error] Target Not Found."));
   } end

} NeoC$
