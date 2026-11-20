#pragma once

#include "pgame_sdk.h"

#include <future>
#include <stdexcept>
#include <string>
#include <utility>

namespace pgame {

enum class Environment {
  Sandbox = PGAME_ENVIRONMENT_SANDBOX,
  Production = PGAME_ENVIRONMENT_PRODUCTION,
  Local = PGAME_ENVIRONMENT_LOCAL,
};

struct Config {
  Environment environment = Environment::Sandbox;
  std::string clientId;
  std::string scope = "openid profile email phone";
  std::string authorizeUrl;
  unsigned int timeoutSeconds = 300;
};

struct LoginResult {
  std::string code;
  std::string state;
  std::string redirectUri;
};

class Error : public std::runtime_error {
public:
  Error(PGameErrorCode code, const std::string &message)
      : std::runtime_error(message), code_(code) {}

  [[nodiscard]] PGameErrorCode code() const noexcept { return code_; }

private:
  PGameErrorCode code_;
};

class Client final {
public:
  explicit Client(const Config &config) {
    PGameConfig native_config{};
    native_config.environment =
        static_cast<PGameEnvironment>(config.environment);
    native_config.client_id = config.clientId.c_str();
    native_config.scope = config.scope.c_str();
    native_config.authorize_url =
        config.authorizeUrl.empty() ? nullptr : config.authorizeUrl.c_str();
    native_config.timeout_seconds = config.timeoutSeconds;

    PGameError error{};
    handle_ = pgame_client_create(&native_config, &error);
    if (!handle_) {
      throw Error(error.code, error.message);
    }
  }

  ~Client() { pgame_client_destroy(handle_); }

  Client(const Client &) = delete;
  Client &operator=(const Client &) = delete;

  Client(Client &&other) noexcept : handle_(other.handle_) {
    other.handle_ = nullptr;
  }

  Client &operator=(Client &&other) noexcept {
    if (this != &other) {
      pgame_client_destroy(handle_);
      handle_ = other.handle_;
      other.handle_ = nullptr;
    }
    return *this;
  }

  [[nodiscard]] LoginResult login() {
    PGameLoginResult result{};
    PGameError error{};
    const auto code = pgame_client_login(handle_, &result, &error);
    if (code != PGAME_OK) {
      throw Error(code, error.message);
    }

    return {result.code, result.state, result.redirect_uri};
  }

  [[nodiscard]] std::future<LoginResult> loginAsync() {
    return std::async(std::launch::async, [this] { return login(); });
  }

  void cancel() noexcept { pgame_client_cancel(handle_); }

  [[nodiscard]] static std::string version() { return pgame_sdk_version(); }

private:
  PGameClient *handle_ = nullptr;
};

} // namespace pgame
