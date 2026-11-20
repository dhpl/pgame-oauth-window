using PGame.Unity;
using PGame.Windows;
using UnityEngine;

public sealed class PGameLoginExample : MonoBehaviour
{
    [SerializeField] private string clientId = "YOUR_CLIENT_ID";

    private PGameUnityClient _client;

    public async void Login()
    {
        _client ??= new PGameUnityClient(clientId);

        try
        {
            var result = await _client.LoginAsync();
            Debug.Log($"PGame code: {result.Code}");
            Debug.Log($"PGame redirect URI: {result.RedirectUri}");
        }
        catch (PGameException error)
        {
            Debug.LogError($"PGame login failed ({error.Code}): {error.Message}");
        }
    }

    private void OnDestroy()
    {
        _client?.Dispose();
    }
}
