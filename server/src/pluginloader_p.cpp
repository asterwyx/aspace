#include "pluginloader_p.h"
#include "pluginloader.h"
#include <QApplication>
#include <QDir>
#include <QString>

namespace dspace {
PluginLoaderPrivate::PluginLoaderPrivate(PluginLoader *q) : q_ptr(q) {}
PluginLoaderPrivate::~PluginLoaderPrivate() = default;

bool PluginLoaderPrivate::loadPlugins() {
    qDebug() << "Enter load plugins.";
    QString appRunPrefix = qApp->applicationDirPath();
    foreach (QString pluginDir, m_pluginDirs)
    {
        QDir pluginsDir(appRunPrefix);
        pluginsDir.cdUp();
        pluginsDir.cd(pluginDir);
        foreach (QString fileName, pluginsDir.entryList(QDir::Files | QDir::Executable)) {
            qDebug() << fileName;
            QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
            QObject *plugin = pluginLoader.instance();
            PluginInterface *loadedInterface = qobject_cast<PluginInterface *>(plugin);
            if (loadedInterface) {
                qDebug() << "Load plugin" << plugin->metaObject()->className() << "successfully!";
                this->m_plugins.push_back(loadedInterface);
            }
        }
    }
    return true;
}
} // namespace dspace