#include <NeoC.h>

void main() $_ {
   String_t *text = String.New(u8"NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   uint8_t target = 'i';
   try {
      defer {
         Map_t *map = Map.New() in (String_t *, Bool_t *);

         map->Put(map, String.New(u8"NeoC!    "), Bool.New(false));
         map->Put(map, String.New(u8"NeoC!!!  "), Bool.New(false));
         map->Put(map, String.New(u8"NeoC!!!!!"), Bool.New(true));

         for (int32_t i = 0; i < map->GetLength(map); i++) {
            Console.WriteLine(String.NewFormat(
               u8"%s : %s",
               String.Unpack( map->Get(map, i).Key ),
               Bool.ToString( map->Get(map, i).Value )
            ));
         }
      } set

      defer {
         Console.WriteLine(text);
         Console.NewLine();
      } set

      execute {
         int32_t fi = String.FirstIndexOf(text, target);
                   // text->FirstIndexOf(text, target);
         int32_t li = text->LastIndexOf(text, target);
                   // String.LastIndexOf(text, target);

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
