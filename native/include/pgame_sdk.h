#ifndef PGAME_SDK_H
#define PGAME_SDK_H

#include <stdint.h>

#if defined(_WIN32)
#if defined(PGAME_SDK_EXPORTS)
#define PGAME_API __declspec(dllexport)
#else
#define PGAME_API __declspec(dllimport)
#endif
#define PGAME_CALL __cdecl
#else
#define PGAME_API
#define PGAME_CALL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define PGAME_CODE_CAPACITY 512
#define PGAME_STATE_CAPACITY 128
#define PGAME_URI_CAPACITY 1024
#define PGAME_ERROR_MESSAGE_CAPACITY 512

typedef struct PGameClient PGameClient;

typedef enum PGameEnvironment {
  PGAME_ENVIRONMENT_SANDBOX = 0,
  PGAME_ENVIRONMENT_PRODUCTION = 1,
  PGAME_ENVIRONMENT_LOCAL = 2
} PGameEnvironment;

typedef enum PGameErrorCode {
  PGAME_OK = 0,
  PGAME_ERROR_INVALID_ARGUMENT = 1,
  PGAME_ERROR_ALREADY_RUNNING = 2,
  PGAME_ERROR_NETWORK = 3,
  PGAME_ERROR_BROWSER = 4,
  PGAME_ERROR_TIMEOUT = 5,
  PGAME_ERROR_CANCELLED = 6,
  PGAME_ERROR_INVALID_CALLBACK = 7,
  PGAME_ERROR_STATE_MISMATCH = 8,
  PGAME_ERROR_OAUTH = 9,
  PGAME_ERROR_INTERNAL = 10
} PGameErrorCode;

typedef struct PGameConfig {
  PGameEnvironment environment;
  const char *client_id;
  const char *scope;
  const char *authorize_url;
  uint32_t timeout_seconds;
} PGameConfig;

typedef struct PGameLoginResult {
  char code[PGAME_CODE_CAPACITY];
  char state[PGAME_STATE_CAPACITY];
  char redirect_uri[PGAME_URI_CAPACITY];
} PGameLoginResult;

typedef struct PGameError {
  PGameErrorCode code;
  char message[PGAME_ERROR_MESSAGE_CAPACITY];
} PGameError;

PGAME_API const char *PGAME_CALL pgame_sdk_version(void);

PGAME_API PGameClient *PGAME_CALL pgame_client_create(const PGameConfig *config,
                                                      PGameError *error);

PGAME_API void PGAME_CALL pgame_client_destroy(PGameClient *client);

/*
 * Blocking login operation. Wrappers should call this on a worker thread.
 * The function opens the system browser, waits for the loopback callback,
 * validates state and returns the one-time authorization code.
 * Starting another login on the same client cancels and replaces an operation
 * that is still waiting for its browser callback.
 */
PGAME_API PGameErrorCode PGAME_CALL pgame_client_login(PGameClient *client,
                                                       PGameLoginResult *result,
                                                       PGameError *error);

PGAME_API void PGAME_CALL pgame_client_cancel(PGameClient *client);

#ifdef __cplusplus
}
#endif

#endif
