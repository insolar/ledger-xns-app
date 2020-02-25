Transaction Specification
-------------------------

### Format

Transactions passed to the Ledger device will be in the following format. The Ledger device MUST accept any transaction (valid as below) in this format.

```json
{
  "jsonrpc":"2.0",
  "id":{number},
  "method":"contract.call",
  "params":
    {
      "callSite": {string},
      "callParams": {...},
      "publicKey": {string},
      "seed": {string}
    }
}
```

`msgs` is a list of messages, which are arbitrary JSON structures.

#### Examples

```json
{"jsonrpc":"2.0","id":1,"method":"contract.call","params":{"callSite":"member.migrationCreate","publicKey":"-----BEGIN PUBLIC KEY-----\nMFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEc+Vs4y+XWE77LR0QL1e1wCOFePFEHJIB\ndsPWPKMH5zGRhRWV1HCJXajENCV2bdG/YKKEOAzTdE5BGXNg2dRQpQ==\n-----END PUBLIC KEY-----","seed":"rOpiqgDHHDmr2PfI5UzZiWpjRyDMoFtBNFoOwyC+yJ8="}}
```

```json
{"jsonrpc":"2.0","id":1,"method":"contract.call","params":{"callSite":"member.transfer","callParams":{"amount":"24000000005","toMemberReference":"insolar:1AAEAATjWvxVC3DFEBqINu7JSKWxlcb_uJo7QdAHrcP8"},"reference":"insolar:1AAEAAY2zkW3pOTCIlYg6XqhWLR32AAeBpTKZ3vLdFhE","publicKey":"-----BEGIN PUBLIC KEY-----\nMFYwEAYHKoZIzj0CAQYFK4EEAAoDQgAEc+Vs4y+XWE77LR0QL1e1wCOFePFEHJIB\ndsPWPKMH5zGRhRWV1HCJXajENCV2bdG/YKKEOAzTdE5BGXNg2dRQpQ==\n-----END PUBLIC KEY-----","seed":"rOpiqgDHHDmr2PfI5UzZiWpjRyDMoFtBNFoOwyC+yJ8="}}
```

### Validation

The Ledger device MUST validate that supplied JSON is valid. Our JSON specification is a subset of [RFC 7159](https://tools.ietf.org/html/rfc7159) - invalid RFC 7159 JSON is invalid Ledger JSON, but not all valid RFC 7159 JSON is valid Ledger JSON.

We add the following two rules:
- No spaces or newlines can be included, other than escaped in strings
- All dictionaries must be serialized in lexicographical key order

This serves to prevent signature compatibility issues among different client libraries.
