// Copyright (c) Duende Software. All rights reserved.
// See LICENSE in the project root for license information.

namespace WEB_153504_Skroba.IdentityServer.Pages.Ciba
{
    public class InputModel
    {
        public string Button { get; set; }
        public IEnumerable<string> ScopesConsented { get; set; }
        public string Id { get; set; }
        public string Description { get; set; }
    }
}