The Windows packaging script copies these files here:

- `PGameSDK.dll`: native x64 OAuth core, under `x86_64/`.
- `PGameSDK.Managed.dll`: managed .NET wrapper, directly under `Plugins/`.

Do not copy a client secret into the Unity project. Login returns an
authorization code that the partner backend exchanges for tokens.
