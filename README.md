# NeoC
Neo C Programming Environment Library

![](https://user-images.githubusercontent.com/85844095/125081210-b6ea7380-e100-11eb-9f34-0871e29de9cc.png)
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;__↑↑↑ examples/Theme.c ↑↑↑__

&emsp;&emsp;&emsp;__↓↓↓ Sample Code (examples/SampleCode.c) ↓↓↓__
```C
#include "NeoC/String.h"
#include "NeoC/Console.h"
#include "NeoC/Exception.h"

void main() $NeoC {
   String_t *text = String.New("NeoC is a Neo C Programming Environment Library !");
   Console.WriteLine(text);

   try {
      int32_t fi = String.FirstIndexOf(text, 'i');
      int32_t li = String.LastIndexOf(text, 'i');

      for (int32_t i = 0; i < String.GetLength(text); i++) {
         Console.WriteChar((i == fi || i == li)? '^' : ' ');
      }
      Console.NewLine();

   } catch (String.RuntimeException) {
      Console.WriteErrorLine(String.New("[Error] Target Not Found."));
   } end

} NeoC$
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
