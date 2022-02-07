/*
{
  "errcode": "<error code>",  // Takes the form M_<ERROR>, <ERROR> being on of the preprocessor definitions below.
  "error": "<error message>" // Human readable error message.
  ??? (optional) "soft_logout": // https://spec.matrix.org/v1.1/client-server-api/#soft-logout
}
*/

/* Common error codes (section 1.1.1) */
#define M_FORBIDDEN                       "M_FORBIDDEN"
#define M_UNKNOWN_TOKEN                   "M_UNKNOWN_TOKEN"
#define M_MISSING_TOKEN                   "M_MISSING_TOKEN"
#define M_BAD_JSON                        "M_BAD_JSON"
#define M_NOT_JSON                        "M_NOT_JSON"
#define M_NOT_FOUND                       "M_NOT_FOUND"
#define M_LIMIT_EXCEEDED                  "M_LIMIT_EXCEEDED"
#define M_UNKNOWN                         "M_UNKNOWN"

/* Other error codes (section 1.1.2) */
#define M_UNRECOGNIZED                    "M_UNRECOGNIZED"
#define M_UNAUTHORIZED                    "M_UNAUTHORIZED"
#define M_USER_DEACTIVATED                "M_USER_DEACTIVATED"
#define M_USER_IN_USE                     "M_USER_IN_USE"
#define M_INVALID_USERNAME                "M_INVALID_USERNAME"
#define M_ROOM_IN_USE                     "M_ROOM_IN_USE"
#define M_THREEPID_IN_USE                 "M_THREEPID_IN_USE"
#define M_THREEPID_NOT_FOUND              "M_THREEPID_NOT_FOUND"
#define M_THREEPID_AUTH_FAILED            "M_THREEPID_AUTH_FAILED"
#define M_THREEPID_DENIED                 "M_THREEPID_DENIED"
#define M_SERVER_NOT_TRUSTED              "M_SERVER_NOT_TRUSTED"
#define M_UNSUPPORTED_ROOM_VERSION        "M_UNSUPPORTED_ROOM_VERSION"
#define M_INCOMPATIBLE_ROOM_VERSION       "M_INCOMPATIBLE_ROOM_VERSION"
#define M_BAD_STATE                       "M_BAD_STATE"
#define M_GUEST_ACCESS_FORBIDDEN          "M_GUEST_ACCESS_FORBIDDEN"
#define M_CAPTCHA_NEEDED                  "M_CAPTCHA_NEEDED"
#define M_CAPTCHA_INVALID                 "M_CAPTCHA_INVALID"
#define M_MISSING_PARAM                   "M_MISSING_PARAM"
#define M_INVALID_PARAM                   "M_INVALID_PARAM"
#define M_TOO_LARGE                       "M_TOO_LARGE"
#define M_EXCLUSIVE                       "M_EXCLUSIVE"
#define M_RESOURCE_LIMIT_EXCEEDED         "M_RESOURCE_LIMIT_EXCEEDED"
#define M_CANNOT_LEAVE_SERVER_NOTICE_ROOM "M_CANNOT_LEAVE_SERVER_NOTICE_ROOM"
