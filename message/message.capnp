@0xdf3cb929d5e9ba92;

struct Image{
    data @0 :Data;
    height @1 :UInt32;
    width @2 :UInt32;
    channels @3 :UInt8;
}

struct Ports{
    const cameraFrame :Int32 = 7777;
    const gpsData :Int32 = 7778;
    const log :Int32 = 7779;
}