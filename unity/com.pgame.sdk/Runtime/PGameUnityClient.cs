using System;
using System.Threading;
using System.Threading.Tasks;
using PGame.Windows;

namespace PGame.Unity
{
    public sealed class PGameUnityClient : IDisposable
    {
        private readonly PGameClient _client;

        public PGameUnityClient(
            string clientId,
            PGameEnvironment environment = PGameEnvironment.Sandbox,
            string scope = "openid profile email phone",
            uint timeoutSeconds = 300,
            string authorizeUrl = null)
        {
            _client = new PGameClient(new PGameConfig
            {
                ClientId = clientId,
                Environment = environment,
                Scope = scope,
                TimeoutSeconds = timeoutSeconds,
                AuthorizeUrl = authorizeUrl,
            });
        }

        public Task<PGameLoginResult> LoginAsync(
            CancellationToken cancellationToken = default)
        {
            return _client.LoginAsync(cancellationToken);
        }

        public void Cancel() => _client.Cancel();

        public void Dispose() => _client.Dispose();
    }
}
