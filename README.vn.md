# **[SAMPVOICE](https://github.com/CyberMor/sampvoice) - [FORKED](https://github.com/ZTzTopia/sampvoice) - [OPEN.MP VERSION](https://github.com/AmyrAhmady/sampvoice/)**
[English](https://github.com/vdgiapp/sampvoice/blob/test/README.md) | [Русский](https://github.com/vdgiapp/sampvoice/blob/test/README.ru.md) | Vietnamese

## Mô tả
---------------------------------
**SAMPVOICE** - là Bộ công cụ phát triển phần mềm (SDK) để triển khai hệ thống giao tiếp voice cho máy chủ SA:MP.

#### Phiên bản hỗ trợ
----------------------------------
* Máy khách: SA:MP 0.3.7 (R1, R3), SA:MP 0.3DL (R1)
* Máy chủ: SA:MP 0.3.7 (R2), SA:MP 0.3DL (R1)

## Tính năng
---------------------------------
* Điều khiển kênh truyền voice
* Điều khiển microphone của người chơi
* Liên kết luồng voice vào vật thể trong game (xe, object,...)
* Và nhiều tính năng khác...

## Cài đặt
---------------------------------
Để plugin hoạt động, nó phải được cả người chơi và máy chủ cài đặt. Có một phần máy khách và máy chủ của plugin cho việc này.

#### Cho người chơi
---------------------------------
Người chơi chọn ngôn ngữ và tải file trực tiếp từ github, sau giải nén ra và bỏ tất cả vào thư mục game.

#### Cho nhà phát triển
---------------------------------
1. Tải từ [`original`](https://github.com/CyberMor/sampvoice/releases) một phiên bản mà bạn muốn cài đặt.
Hoặc phiên bản [`open.mp`](https://github.com/AmyrAhmady/sampvoice/releases) để tích hợp vào open.mp.
2. Giải nén ra bỏ vào thư mục máy chủ.
3. Thêm vào file *server.cfg* dòng *"plugins sampvoice"* cho *Win32* và *"plugins sampvoice.so"* cho *Linux x86*. **(Nếu bạn có plugin Pawn.RakNet hãy để nó trước SampVoice)**

## Cách dùng
---------------------------------
Để sử dụng `sampvoice` trong máy chủ, thêm dòng sau vào đầu gamemode của bạn:
```php
#include <a_samp> // if you dont have open.mp
#include <open.mp> // if you have open.mp
#include <sampvoice>
```

#### Tham khảo
---------------------------------
Bạn cần biết rằng plugin sử dụng từng loại riêng và hệ thống tĩnh. Mặc dù thực tế rằng đây chỉ là một wrapper cho PAWN cơ bản, nhưng nó giúp điều hướng các loại plugin và không gây nhầm lẫn cho các con trỏ.

Để chuyển hướng lưu lượng âm thanh từ trình phát A sang trình phát B, bạn cần tạo một luồng âm thanh (ví dụ: luồng âm thanh toàn cầu, sử dụng **SvCreateGStream**), sau đó Gán nó vào luồng của trình phát A làm loa (sử dụng **SvAttachSpeakerToStream**), sau đó gán vào luồng của người chơi B với tư cách là người nghe (sử dụng **SvAttachListenerToStream**). Xong. Bây giờ, khi micrô của người chơi A được kích hoạt (ví dụ: với chức năng **SvStartRecord**), lưu lượng âm thanh của anh ấy sẽ được truyền đi và sau đó được người chơi B nghe thấy.

Luồng âm thanh khá tiện dụng. Chúng có thể được hình dung bằng ví dụ về Discord:
* Luồng là một dạng tương tự của một phòng (hoặc kênh).
* Diễn giả là những người tham gia trong phòng bị tắt tiếng nhưng vẫn bật micrô.
* Người nghe là những người tham gia trong phòng với micrô của họ bị tắt tiếng.

Người chơi có thể vừa là người nói vừa là người nghe cùng một lúc. Trong trường hợp này, lưu lượng âm thanh của người chơi sẽ không được chuyển tiếp đến anh ta.

#### Ví dụ
---------------------------------
Chúng ta hãy xem một số tính năng của plugin bằng một ví dụ thực tế. Dưới đây, chúng tôi sẽ tạo một máy chủ sẽ liên kết tất cả người chơi được kết nối với luồng toàn cầu, đồng thời tạo luồng cục bộ cho mỗi người chơi. Do đó, người chơi sẽ có thể giao tiếp thông qua các cuộc trò chuyện toàn cầu (được nghe như nhau ở bất kỳ điểm nào trên bản đồ) và cục bộ (chỉ được nghe ở gần người chơi).
```php

new SV_GSTREAM:gstream = SV_NULL;
new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };

/*
    OnPlayerActivationKeyPress và OnPlayerActivationKeyRelease
    là cần thiết để chuyển hướng lưu lượng âm thanh của trình phát đến
    luồng tương ứng khi nhấn các phím tương ứng.
*/

public SV_VOID:OnPlayerActivationKeyPress(SV_UINT:playerid, SV_UINT:keyid) 
{
    // Gán trình phát vào luồng cục bộ làm loa nếu nhấn phím 'B'
    if (keyid == 0x42 && lstream[playerid]) SvAttachSpeakerToStream(lstream[playerid], playerid);
    // Gán trình phát vào luồng toàn cầu dưới dạng loa nếu nhấn phím 'Z'
    if (keyid == 0x5A && gstream) SvAttachSpeakerToStream(gstream, playerid);
}

public SV_VOID:OnPlayerActivationKeyRelease(SV_UINT:playerid, SV_UINT:keyid)
{
    // Gỡ trình phát khỏi luồng cục bộ nếu phím 'B' được nhả
    if (keyid == 0x42 && lstream[playerid]) SvDetachSpeakerFromStream(lstream[playerid], playerid);
    // Gỡ trình phát khỏi luồng toàn cầu nếu phím 'Z' được nhả
    if (keyid == 0x5A && gstream) SvDetachSpeakerFromStream(gstream, playerid);
}

public OnPlayerConnect(playerid)
{
    // Kiểm tra plugin có tồn tại hay có được load hay không
    if (SvGetVersion(playerid) == SV_NULL)
    {
        SendClientMessage(playerid, -1, "Could not find plugin sampvoice.");
    }
    // Kiểm tra microphone của người chơi
    else if (SvHasMicro(playerid) == SV_FALSE)
    {
        SendClientMessage(playerid, -1, "The microphone could not be found.");
    }
    // Tạo luồng cục bộ với khoảng cách nghe được là 40.0, số lượng người nghe không giới hạn (-1)
    // và tên 'Local' (tên 'Local' sẽ được hiển thị màu đỏ trong danh sách người nói của người chơi)
    else if ((lstream[playerid] = SvCreateDLStreamAtPlayer(40.0, SV_INFINITY, playerid, 0xff0000ff, "Local")))
    {
        SendClientMessage(playerid, -1, "Press Z to talk to global chat and B to talk to local chat.");

        // Gán trình phát vào luồng toàn cầu với tư cách là người nghe
        if (gstream) SvAttachListenerToStream(gstream, playerid);

        // Gán phím kích hoạt micrô cho người chơi
        SvAddKey(playerid, 0x42);
        SvAddKey(playerid, 0x5A);
    }
}

public OnPlayerDisconnect(playerid, reason)
{
    // Xóa luồng cục bộ của người chơi sau khi ngắt kết nối
    if (lstream[playerid])
    {
        SvDeleteStream(lstream[playerid]);
        lstream[playerid] = SV_NULL;
    }
}

public OnGameModeInit()
{
    // Bỏ ghi chú dòng để bật chế độ gỡ lỗi
    // SvDebug(SV_TRUE);

    gstream = SvCreateGStream(0xffff0000, "Global");
}

public OnGameModeExit()
{
    if (gstream) SvDeleteStream(gstream);
}
```

## Biên dịch
---------------------------------
Biên dịch plugin cho *Win32* và *Linux x86*.

Dưới đây là hướng dẫn thêm:

Sao chép repo vào máy tính của bạn và đi tới thư mục plugin:
```sh
git clone https://github.com/CyberMor/sampvoice.git
cd sampvoice
```

### Windows (Máy khách/máy chủ)
---------------------------------
Để biên dịch phía máy khách của plugin, bạn cần có *DirectX SDK*. Theo mặc định, phần máy khách được biên dịch cho phiên bản **SA: MP 0.3.7 (R1)**, nhưng bạn cũng có thể cho trình biên dịch biết rõ ràng phiên bản của bản dựng bằng cách sử dụng **SAMP_R1** và **SAMP_R3** macro. Để xây dựng các phần máy khách và máy chủ của plugin cho nền tảng *Win32*, hãy mở dự án *sampvoice.sln* trong MS Visual Studio và biên dịch nó:
> Build -> Build Solution (F7)

### Linux (Máy chủ)
---------------------------------
Để xây dựng phần máy chủ của plugin cho nền tảng *Linux x86*, hãy làm theo các hướng dẫn sau:
```sh
cd server
make
```
