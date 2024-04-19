# ROUTES DOCUMENTATION

## Users

- ### Login

  - Method: `POST`
  - Route: `/login`
  - Request:

    - Params: _No params_
    - Body:

    ```json
        {
            "username": "String"
        }
    ```
  - Response:

    ```json
    {
        "user_uuid": "String"
    }
    ```
  - Possible status codes:

    - <p class="success"><b>200</b> - Successful</p>
    - <p class="success"><b>201</b> - Successful: created user</p>
    - <p class="error"><b>400</b> - Invalid body</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Logout

  - Method: `POST`
  - Route: `/logout`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No Body_
  - Response: _Nothing_
  - Possible status codes:

    - <p class="success"><b>204</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>409</b> - Already offline</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### List user

  - Method: `GET`
  - Route: `/users`
  - Request:

    - Params: `only-connected: Boolean (Optional, default false)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:
    ```json
    [
        {
            "uuid": "String",
            "name": "String",
            "status": "String"
        }
    ]
    ```
  - Possible status codes:

    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Get info of an user

  - Method: `GET`
  - Route: `/user`
  - Request:

    - Params: `uuid: String (Optional, default current user)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:
    ```json
        {
            "uuid": "String",
            "name": "String",
            "status": "String"
        }
    ```
  - Possible status codes:
    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>404</b> - Client not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>

## Messages

- ### Send Message

  - Method: `POST`
  - Route: `/messages/send`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:
    ```json
        {
            "recipient_uuid": "String",
            "message": {
                "content": "String"
            }
        }
    ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success"><b>204</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>404</b> - Receiver not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Direct Message

  - Method: `GET`
  - Route: `/messages`
  - Request:

    - Params: `uuid: String (Mandatory)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:
    ```json
    [
        {
            "sender_uuid": "String",
            "content": "String",
            "timestamp": Number,
        }
    ]
    ```
  - Possible status codes:
    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>404</b> - Target not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>

## Teams

- ### Join Team

  - Method: `POST`
  - Route: `/teams/join`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token`
    - Body:
    ```json
        {
            "team_uuid": "String"
        }
    ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success"><b>204</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>409</b> - Already joined </p>
    - <p class="error"><b>404</b> - Team not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Leave Team

  - Method: `POST`
  - Route: `/teams/leave`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:

    ```json
        {
            "team_uuid": "String"
        }
    ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success"><b>204</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>409</b> - Not in team</p>
    - <p class="error"><b>404</b> - Team not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Get Teams

  - Method: `GET`
  - Route: `/teams`
  - Request:

    - Params:
      - `team-uuid: String (Optional)`
      - `only-joined: Boolean (Optional, default: false, incompatible with team-uuid)`
    - Headers: 
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:

    ```json
    [
        {
            "team_uuid": "String",
            "team_name": "String",
            "team_description": "String"
        }
    ]
    ```
  - Possible status codes:
    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>404</b> - Team not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
  
- ### Create Team

  - Method: `POST`
  - Route: `/teams/create`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:

    ```json
        {
            "name": "String",
            "description": "String"
        }
    ```
  - Response:

    ```json
        {
            "team_uuid": "String"
        }
    ```
  - Possible status codes:
    - <p class="success"><b>201</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>500</b> - Internal server error</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Get Team Users

  - Method: `GET`
  - Route: `/teams/users`
  - Request:

    - Params:
      - `team-uuid: String (mandatory)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:

    ```json
    [
        {
            "uuid": "String",
            "username": "String",
            "status": "String"
        }
    ]
    ```
  - Possible status codes:
    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden</p>
    - <p class="error"><b>404</b> - Team not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>

## Channels

- ### Get Team Channels

  - Method: `GET`
  - Route: `/teams/channels`
  - Request:

    - Params: 
      - `channel-uuid: String (Optional)`
      - `team-uuid: String (Mandatory)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:

    ```json
    [
        {
            "uuid": "String",
            "name": "String",
            "description": "String"
        }
    ]
    ```
  - Possible status codes:
    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden (Not in team)</p>
    - <p class="error"><b>404</b> - Team not found / Channel not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Create Channel

  - Method: `POST`
  - Route: `/teams/channels/create`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:

    ```json
        {
            "team_uuid": "String",
            "name": "String",
            "description": "String"
        }
    ```
  - Response:

    ```json
        {
            "channel_uuid": "String"
        }
    ```
  - Possible status codes:
    - <p class="success"><b>201</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden client not subscribed</p>
    - <p class="error"><b>404</b>- Team not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Get Team Channels Threads

  - Method: `GET`
  - Route: `/teams/channels/threads`
  - Request:

    - Params: 
      - `thread-uuid: String (Optional)`
      - `team-uuid: String (Mandatory)`
      - `channel-uuid: String (Mandatory)`
    - Headers:
      - Authorization: `Bearer <token>`
    - Body: _No body_
  - Response:

    ```json
    [
        {
            "thread_uuid": "String",
            "title": "String",
            "message": "String",
            "timestamp": Number
        }
    ]
    ```
  - Possible status codes:

    - <p class="success"><b>204</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden (Not in team)</p>
    - <p class="error"><b>404</b> - Team not found / Channel not found / Thread not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>

## Threads

- ### Create Thread

  - Method: `POST`
  - Route: `/teams/channels/threads/create`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:

    ```json
        {
            "team_uuid": "String",
            "channel_uuid": "String",
            "title": "String",
            "message": "String"
        }
    ```
  - Response:

    ```json
        {
            "thread_uuid": "String"
        }
    ```
  - Possible status codes:

    - <p class="success"><b>201</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden (Not in team)</p>
    - <p class="error"><b>404</b> - Team not found / Channel not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Get Thread Messages

  - Method: `GET`
  - Route: `/teams/channels/threads/messages`
  - Request:

    - Params: 
      - `team-uuid: String (Mandatory)`
      - `channel-uuid: String (Mandatory)`
      - `thread-uuid: String (Mandatory)`
    - Headers:
      - Authorization: `Bearer
    - Body: _No body_
    
  - Response:

    ```json
    [
        {
            "sender_uuid": "String",
            "content": "String",
            "timestamp": Number
        }
    ]
    ```
  - Possible status codes:

    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Missing authorization / Invalid authorization</p>
    - <p class="error"><b>403</b> - Forbidden (Not in team)</p>
    - <p class="error"><b>404</b> - Team not found / Channel not found / Thread not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>
  
- ### Reply to Thread

  - Method: `POST`
  - Route: `/teams/channels/threads/reply`
  - Request:

    - Params: _No params_
    - Headers:
      - Authorization: `Bearer <token>`
    - Body:

    ```json
        {
            "team_uuid": "String",
            "channel_uuid": "String",
            "thread_uuid": "String",
            "message": {
                "content": "String"
            }
        }
    ```
  - Response: _Nothing_
  - Possible status codes:

    - <p class="success"><b>200</b> - Successful</p>
    - <p class="error"><b>400</b> - Request malformed</p>
    - <p class="error"><b>401</b> - Not connected</p>
    - <p class="error"><b>403</b> - Forbidden (Not in team)</p>
    - <p class="error"><b>404</b> - Team not found / Channel not found / Thread not found</p>
    - <p class="error"><b>405</b> - Method not allowed</p>

<style>
    .success {
        color: #a3e635;
    }
    .error {
        color: #ef4444;
    }
</style>
