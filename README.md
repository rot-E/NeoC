# NeoC
Neo C Programming Environment Library

![](https://user-images.githubusercontent.com/85844095/125081210-b6ea7380-e100-11eb-9f34-0871e29de9cc.png)
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;__↑↑↑ examples/Theme.c ↑↑↑__

&emsp;&emsp;&emsp;__↓↓↓ Sample Code (examples/SampleCode.c) ↓↓↓__
```C
#include "NeoC/Environment.h"
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"
#include "NeoC/Defer.h"
#include "NeoC/System.h"

void main() $_ {
   String_t *text = String.New("NeoC is a Neo C Programming Environment Library !");
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
      Console.WriteErrorLine(String.NewFormat("Target character '%c' not found.", target));
   } fin
} _$
```
<br>

## Build
```fish
$ sh build.sh
```
`NeoC/*.h` `NeoC.a` `examples/*`
<br><br>

## Clean
```fish
$ sh build.sh clean
```
<br>

## License
&emsp;[`AGPLv3`](https://www.gnu.org/licenses/agpl-3.0.html)
