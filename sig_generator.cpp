#include "vimme.h"
#include "video_window.h"

void Vimme::generate_sig(QString & sig)
{
    unsigned int random = (qrand() % ((high + 1) - low) + low);
    switch (random) {
    case 1:
        sig = "292a6b0a1d4f56c914651fc9ad00ba9a";
        break;
    case 2:
        sig = "f80dbb01cdaec19764aadff6ebf87e8c";
        break;
    case 3:
        sig = "bbd4e4b099d38da73d4aa2cbc859d1df";
        break;
    case 4:
        sig = "c1457f860a47e194fcd4d503158f427a";
        break;
    case 5:
        sig = "cfb9cc69d49a0718dbe621bf40c9826a";
        break;
    case 6:
        sig = "dbfea18b72464bd041a96a98a2c6c286";
        break;
    case 7:
        sig = "bc162c8d89df0f799e82413868af7523";
        break;
    case 8:
        sig = "1c230f3b06ef141709843e96837944fb";
        break;
    case 9:
        sig = "47d42975afe9bc916986263aabda1d73";
        break;
    case 10:
        sig = "f8a6977ec54459746d88c75f09702e05";
        break;
    case 11:
        sig = "f990970b0ab92c76a4e93f2ee87e86a7";
        break;
    case 12:
        sig = "2c2a852fd080685c305d9183fb8d635a";
        break;
    case 13:
        sig = "210b2ad4a137aa4845dee8d36c79f3aa";
        break;
    case 14:
        sig = "42d7ced04d6491226686495894dd99bf";
        break;
    case 15:
        sig = "fff4ad9612538c2346383d2885a73224";
        break;
    case 16:
        sig = "944b45863f536c32868e48130cd71781";
        break;
    case 17:
        sig = "017bdf784a4c2aebe75e2ce36495f81f";
        break;
    case 18:
        sig = "69482c3d81009dced5e464f42626f0e4";
        break;
    case 19:
        sig = "b1065472799e15b69140e9ec892868c0";
        break;
    case 20:
        sig = "441a2cea98ecd53367d2752da491330d";
        break;
    case 21:
        sig = "655832b18271024f6add0907842d1978";
        break;
    case 22:
        sig = "372237228f936ac60986fb95f920aa4c";
        break;
    case 23:
        sig = "66513285a85542ec173bd2be3a734f8f";
        break;
    case 24:
        sig = "6aeb809c2949942eb4495ee678d75bf6";
        break;
    case 25:
        sig = "fa13f22d6ecbd25adfc4e312a4c39d75";
        break;
    case 26:
        sig = "45ae138c380ec7ff496b41baa8725e8b";
        break;
    case 27:
        sig = "9a10e4a19b9c0108bfec4c1008ae15a3";
        break;
    case 28:
        sig = "c9ffcb55ea0102ac771eb7d6d86772a9";
        break;
    case 29:
        sig = "ac6b52053c088d9e4595f979adcd9c0c";
        break;
    case 30:
        sig = "d11646753150a70548a73f0093fe2151";
        break;
    case 31:
        sig = "bf31c32cdc83438f9d465277184ef29c";
        break;
    default:
        break;
    }
    qDebug() << "sig = " << sig;
}

void Video_window::generate_video_sig(QString & sig)
{
    unsigned int random = (qrand() % ((high + 1) - low) + low);
    switch (random) {
    case 1:
        sig = "6f8245d537a3760b2286c709f86e69df";
        break;
    case 2:
        sig = "a14db0e1f13944e60b64959d8331ab39";
        break;
    case 3:
        sig = "094eb42c093d222b4f7648c354cf5b4f";
        break;
    case 4:
        sig = "49ae9fcd1d4e1b8fb720dfb31b22c546";
        break;
    case 5:
        sig = "208a0d19f96032f491b394ea24a15f9e";
        break;
    case 6:
        sig = "745256eed60bc139eb7102a92a6b1cd8";
        break;
    case 7:
        sig = "533d8d48b6fc6bd769262f7ad005b08b";
        break;
    case 8:
        sig = "bb07b6a68ba2a34b2cba1a6c88ffc312";
        break;
    case 9:
        sig = "63048b3c7a4c2eff1fc56db87b549b75";
        break;
    case 10:
        sig = "bc12e5a60d658c0c4a98110c20c62948";
        break;
    case 11:
        sig = "a5ffe08e4946735294774cafe8124f9d";
        break;
    case 12:
        sig = "e9696e685a8beded50afa1804f8ea9d0";
        break;
    case 13:
        sig = "8753747b94fdf2b0f6a48bceb3743e72";
        break;
    case 14:
        sig = "1e7e1b079367713e3a6a9aabc7a9e9ed";
        break;
    case 15:
        sig = "dec8651698a508276d9b7fa68b49bacc";
        break;
    case 16:
        sig = "74ba85a0305ec53d4f0a834bc89692de";
        break;
    case 17:
        sig = "b26d4be67a36122d62d80e8148991dc4";
        break;
    case 18:
        sig = "273f457fb593862da3e693adc76a7c28";
        break;
    case 19:
        sig = "97a7aaba16ceb617561e970a11193f54";
        break;
    case 20:
        sig = "23499b10b5ca0eeaca6441d6b98a309f";
        break;
    case 21:
        sig = "ad68fa3bfea96981b36d1c2eb09976fa";
        break;
    case 22:
        sig = "1b044c5a67ee2eb93ed172dff016cc97";
        break;
    case 23:
        sig = "c4cf641c181ce2265c865ee1fc3b3f70";
        break;
    case 24:
        sig = "4ef34270268f32ba96f11be390f068e0";
        break;
    case 25:
        sig = "bf20cf61d0d76e31c2f7506d6f7e66cf";
        break;
    case 26:
        sig = "c96389f359465fafa1782a7bf587796d";
        break;
    case 27:
        sig = "6220edaa821bcd334e334d9a585d0c1d";
        break;
    case 28:
        sig = "da038a6f3e24d2b56d458f7e18b11caf";
        break;
    case 29:
        sig = "7de7f947ae53f6cf47f6765d4032838a";
        break;
    case 30:
        sig = "9cdc50fd05921568c7f035ce2989e512";
        break;
    case 31:
        sig = "a6509e9bf3fe33a820de7460c965f911";
        break;
    default:
        break;
    }
    qDebug() << "sig = " << sig;
}
