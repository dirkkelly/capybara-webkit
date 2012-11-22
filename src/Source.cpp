#include "Source.h"
#include "WebPage.h"
#include "WebPageManager.h"
#include "NetworkAccessManager.h"

Source::Source(WebPageManager *manager, QStringList &arguments, QObject *parent) : SocketCommand(manager, arguments, parent) {
}

void Source::start() {
  NetworkAccessManager* accessManager = page()->networkAccessManager();
  QNetworkRequest request(page()->currentFrame()->requestedUrl());
  reply = accessManager->get(request);

  connect(reply, SIGNAL(finished()), this, SLOT(sourceLoaded()));
}

void Source::sourceLoaded() {
  emit finished(new Response(true, reply->readAll()));
}

