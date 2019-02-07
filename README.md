# Matrix Graphics for atmega328p

Looks a little something like [this](https://www.youtube.com/watch?v=9mhROI0bKPY).

To build and flash to atmega328p: ` make dfu `

To enable UART debugging build with `DEBUG=1`, `DEBUG=2`, `DEBUG=3` for `INFO`, `TRACE`, `DEBUG` log levels respectively.
UART receiver should be set to 8 bit data, no parity bit, 1 stop bit with a baud rate of 9600.

## Led Matrix Construction

Pick up four 8x8 common-cathode led matrices like [this one](https://www.aliexpress.com/item/FREE-SHIPPING-10PCS-x-3MM-8X8-Blue-32-32-Square-LED-Dot-Matrix-Digital-Tube-Module/32756523226.html?spm=2114.search0104.3.2.5ecc56f4yLp0YW&ws_ab_test=searchweb0_0,searchweb201602_3_10065_10068_10890_319_10546_10059_10884_317_10548_10887_10696_321_322_10084_453_10083_454_10103_10618_10307_537_536_10902,searchweb201603_51,ppcSwitch_0&algo_expid=a0eba49f-bad1-461f-b187-3f820354756a-0&algo_pvid=a0eba49f-bad1-461f-b187-3f820354756a), and four [MAX7219](https://www.maximintegrated.com/en/products/power/display-power-control/MAX7219.html) led matrix drivers. The drivers should be daisy-chained in the order of top-left, top-right, bottom-left, bottom-right. The rows correspond to anodes and columns cathodes. The matrices should have orientation with "top" facing the left.

## Test
To run tests, `cd` to test directory and run `make test`. Note that the tests are compiled to PC architecture via `gcc` and only test non-hardware specific code.
