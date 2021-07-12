#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"
#include "NeoC/Defer.h"
#include "NeoC/System.h"

void main() $_ {
   String_t *text = String.New(u8"NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   uint8_t target = 'i';
   try {
      defer {
         Console.WriteLine(text);
      } set

      execute {
         int32_t fi = String.FirstIndexOf(text, target);
         int32_t li = String.LastIndexOf(text, target);

         for (int32_t i = 0; i < String.GetLength(text); i++) {
            Console.WriteChar((i == fi || i == li)? '^' : ' ');
         System.USleep(50 * 1000);
         }
         Console.NewLine();
      } ret
   } catch (String.Failure) {
      Console.WriteErrorLine(String.NewFormat(u8"Target character '%c' not found.", target));
   } fin
} _$
