#include "NeoC/Exception.h"
#include "NeoC/String.h"
#include "NeoC/CC.h"

#include <stdio.h>

void main() $NeoC {
   String_t *text = String.New("NeoC is a Neo C Programming Environment Library !");
   printf("%s%c", String.Unpack(text), CC.LF);

   try {
      int32_t fm = String.FirstIndexOf(text, 'i');
      int32_t lm = String.LastIndexOf(text, 'i');

      for (int32_t i = 0; i < String.GetLength(text); i++) {
         printf("%c", (i == fm || i == lm)? '^' : ' ');
      }
      printf("%c", CC.LF);
      
   } catch (String.RuntimeException) {
      printf("[Error] Target Not Found.\n");
   } end

} NeoC$
