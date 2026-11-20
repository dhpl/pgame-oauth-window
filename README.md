# PGame OAuth SDK for Windows

SDK OAuth cho game Windows, Cocos, Unity, Java và libGDX. Phiên bản hiện tại là `1.3.11`, hỗ trợ Windows x64.

## C++/Cocos với CMake

```bash
git submodule add https://github.com/dhpl/pgame-oauth-window.git third_party/pgame-oauth-window
```

```cmake
add_subdirectory(third_party/pgame-oauth-window)
target_link_libraries(your_game PRIVATE PGameSDK::PGameSDK)
```

Copy `native/bin/PGameSDK.dll` cạnh file `.exe` khi đóng gói game.

```cpp
#include <PGameSDK.hpp>

pgame::Config config;
config.environment = pgame::Environment::Production;
config.clientId = "YOUR_CLIENT_ID";

pgame::Client client(config);
auto login = client.loginAsync();
auto result = login.get(); // Chờ trên worker thread.
```

## C#/.NET và Unity

Thêm `csharp/PGameSDK.csproj` hoặc tham chiếu `csharp/PGameSDK.Managed.dll`, rồi đặt `native/bin/PGameSDK.dll` cạnh executable.

Với Unity Package Manager, chọn **Add package from disk** và mở `unity/com.pgame.sdk/package.json`. Package đã chứa C# wrapper và Windows x86_64 plugin.

## Java và libGDX

Thêm `java/pgame-sdk-windows-java-1.3.11.jar` vào classpath. JAR hiện tại vẫn giữ nguyên API/package. Đặt `java/PGameSDK.dll` và `java/PGameSDKJNI.dll` trong `java.library.path`.

libGDX dùng thêm `gdx/pgame-sdk-windows-gdx-1.3.11.jar`; callback được chuyển về libGDX application thread.

SDK mở trình duyệt mặc định, nhận OAuth callback qua loopback và trả `code`, `state`, `redirectUri`. Backend game dùng nguyên văn `redirectUri` để đổi code lấy token. Không đặt `clientSecret` trong game.

Đăng ký redirect URI `http://127.0.0.1/pgame-callback` trong Partner App.
