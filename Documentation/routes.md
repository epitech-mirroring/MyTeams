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
    - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="success">201 - Successful: new user</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">403 - Already connected</p>
   
  
- ### Logout
  - Method: `POST`  
  - Route: `/logout`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String"
        }
      ```  
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
  
  
- ### List user
  - Method: `GET`
  - Route: `/users`
  - Request:
    - Params: `only-connected: Boolean (Optional, default false)`
    - Body:
    ```json
        {
            "user_uuid": "String"
        }
      ```
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
  
  
- ### Get info of an user
  - Method: `GET`
  - Route: `/user`
  - Request:
    - Params: `uuid: String (Optional, default current user)`
    - Body:
    ```json
        {
            "user_uuid": "String"
        }
      ```
  - Response:
    ```json
        {
            "uuid": "String",
            "name": "String",
            "status": "String"
        }
    ```
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">404 - User not found</p>
## Messages

- ### Send Message
  - Method: `POST`
  - Route: `/messages/send`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
            "recipient_uuid": "String",
            "message": {
                "content": "String"
            }
        }
      ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">404 - Recipient not found</p>
  
- ### Direct Message
  - Method: `GET`
  - Route: `/messages`
  - Request:
    - Params: `uuid: String (Mandatory)`
    - Body:
    ```json
        {
            "user_uuid": "String"
        }
      ```
  - Response:
    ```json
    [
        {
            "sender_uuid": "String",
            "message": {
                "content": "String"
            }
        }
    ]
    ```
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">404 - Target not found</p>
  
## Teams
- ### Join Team
  - Method: `POST`
  - Route: `/teams/join`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String"
        }
      ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Already in team</p>
    - <p class="error">404 - Team not found</p>

- ### Leave Team
  - Method: `POST`
  - Route: `/teams/leave`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String"
        }
      ```
  - Response: _Nothing_
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Not in team</p>
    - <p class="error">404 - Team not found</p>
  
- ### Get Teams
  - Method: `GET`
  - Route: `/teams`
  - Request:
    - Params: 
      - `team-uuid: String (Optional)`
      - `only-joined: Boolean (Optional, default: false, incompatible with team-uuid)`
    - Body:
    ```json
        {
            "user_uuid": "String"
        }
      ```
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">404 - Team not found</p>

- ### Create Team
  - Method: `POST`
  - Route: `/teams/create`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed / Name or description too long</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Already exists)</p>

- ### Get Team Users
  - Method: `GET`
  - Route: `/teams/users`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String"
        }
      ```
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden</p>
    - <p class="error">404 - Team not found</p>

## Channels
- ### Get Team Channels
  - Method: `GET`
  - Route: `/teams/channels`
  - Request:
    - Params: `channel_uuid: String (Optional)`
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String"
        }
      ```
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team)</p>
    - <p class="error">404 - Team not found / Channel not found</p>

- ### Create Channel
  - Method: `POST`
  - Route: `/teams/channels/create`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team) / Forbidden (Already exists)</p>
    - <p class="error">404 - Team not found</p>
  
- ### Get Team Channels Threads
  - Method: `GET`
  - Route: `/teams/channels/threads`
  - Request:
    - Params: `thread_uuid: String (Optional)`
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String",
            "channel_uuid": "String"
        }
      ```
  - Response:
    ```json
    [
        {
            "thread_uuid": "String",
            "title": "String",
            "message": "String"
        }
    ]
    ```
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team)</p>
    - <p class="error">404 - Team not found / Channel not found / Thread not found</p>
  
- ### Create Thread
  - Method: `POST`
  - Route: `/teams/channels/threads/create`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team) / Forbidden (Already exists)</p>
    - <p class="error">404 - Team not found / Channel not found</p>

- ### Get Thread Messages
  - Method: `GET`
  - Route: `/teams/channels/threads/messages`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
            "team_uuid": "String",
            "channel_uuid": "String",
            "thread_uuid": "String"
        }
      ```
  - Response:
    ```json
    [
        {
            "sender_uuid": "String",
            "message": {
                "content": "String"
            }
        }
    ]
    ```
  - Possible status codes:
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team)</p>
    - <p class="error">404 - Team not found / Channel not found / Thread not found</p>

- ### Reply to Thread
  - Method: `POST`
  - Route: `/teams/channels/threads/reply`
  - Request:
    - Params: _No params_
    - Body:
    ```json
        {
            "user_uuid": "String",
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
    - <p class="success">200 - Successful</p>
    - <p class="error">400 - Request malformed</p>
    - <p class="error">401 - Not connected</p>
    - <p class="error">403 - Forbidden (Not in team)</p>
    - <p class="error">404 - Team not found / Channel not found / Thread not found</p>
  
<style>
    .success {
        color: #a3e635;
    }
    .error {
        color: #ef4444;
    }
</style>