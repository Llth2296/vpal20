var assert    = require('assert');
var extend    = require("extend");
var Server    = require("./server").Server;
var Remote    = require("ripple-lib").Remote;
var testutils = require('./testutils');
var config    = testutils.init_config();

suite('WebSocket connection', function() {
  var server;

  setup(function(done) {
    this.timeout(2000);

    var cfg = extend({}, config.default_server_config, config.servers.alpha);
    if (cfg.no_server) {
      done();
    } else {
      server = Server.from_config("alpha", cfg);
      server.once('started', done)
      server.start();
    }
  });

  teardown(function(done) {
    this.timeout(2000);
    
    if (config.servers.alpha.no_server) {
      done();
    } else {
      server.on('stopped', done);
      server.stop();
    }
  });

  test('WebSocket connect and disconnect', function(done) {
    // This timeout probably doesn't need to be this long, because
    // the test itself completes in less than half a second. 
    // However, some of the overhead, especially on Windows can
    // push the measured time out this far.
    this.timeout(3000);

    var alpha = Remote.from_config("alpha");

    alpha.on('connected', function () {
      alpha.on('disconnected', function () {
        // CLOSED
        done();
      });
      alpha.connect(false);
    })

    alpha.connect();
  });
});

// vim:sw=2:sts=2:ts=8:et