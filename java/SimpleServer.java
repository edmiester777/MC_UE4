package ue.test;

import com.mojang.authlib.GameProfileRepository;
import com.mojang.authlib.minecraft.MinecraftSessionService;
import com.mojang.authlib.yggdrasil.YggdrasilAuthenticationService;
import com.mojang.serialization.Lifecycle;
import net.minecraft.CrashReport;
import net.minecraft.SharedConstants;
import net.minecraft.Util;
import net.minecraft.commands.Commands;
import net.minecraft.core.RegistryAccess;
import net.minecraft.nbt.NbtOps;
import net.minecraft.nbt.Tag;
import net.minecraft.obfuscate.DontObfuscate;
import net.minecraft.resources.RegistryReadOps;
import net.minecraft.server.Bootstrap;
import net.minecraft.server.MinecraftServer;
import net.minecraft.server.ServerResources;
import net.minecraft.server.dedicated.DedicatedServer;
import net.minecraft.server.dedicated.DedicatedServerProperties;
import net.minecraft.server.dedicated.DedicatedServerSettings;
import net.minecraft.server.level.progress.LoggerChunkProgressListener;
import net.minecraft.server.packs.PackType;
import net.minecraft.server.packs.repository.FolderRepositorySource;
import net.minecraft.server.packs.repository.PackRepository;
import net.minecraft.server.packs.repository.PackSource;
import net.minecraft.server.packs.repository.ServerPacksSource;
import net.minecraft.server.players.GameProfileCache;
import net.minecraft.util.datafix.DataFixers;
import net.minecraft.world.level.DataPackConfig;
import net.minecraft.world.level.GameRules;
import net.minecraft.world.level.LevelSettings;
import net.minecraft.world.level.levelgen.WorldGenSettings;
import net.minecraft.world.level.storage.*;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.awt.*;
import java.io.File;
import java.net.Proxy;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.concurrent.CompletableFuture;

public class SimpleServer {
    public static DedicatedServer SERVER;
    private static final Logger LOGGER = LogManager.getLogger();

    @DontObfuscate
    public static void main(String rootPath) {
        SharedConstants.tryDetectVersion();
        try {
            CrashReport.preload();

            Bootstrap.bootStrap();
            Bootstrap.validate();
            Util.startTimerHackThread();
            RegistryAccess.RegistryHolder registryaccess$registryholder = RegistryAccess.builtin();
            Path path = Paths.get(rootPath + "/server.properties");
            DedicatedServerSettings dedicatedserversettings = new DedicatedServerSettings(path);
            dedicatedserversettings.forceSave();

            File file1 = new File(rootPath + "/universe");
            YggdrasilAuthenticationService yggdrasilauthenticationservice = new YggdrasilAuthenticationService(Proxy.NO_PROXY);
            MinecraftSessionService minecraftsessionservice = yggdrasilauthenticationservice.createMinecraftSessionService();
            GameProfileRepository gameprofilerepository = yggdrasilauthenticationservice.createProfileRepository();
            GameProfileCache gameprofilecache = new GameProfileCache(gameprofilerepository, new File(file1, MinecraftServer.USERID_CACHE_FILE.getName()));
            String s = dedicatedserversettings.getProperties().levelName;
            LevelStorageSource levelstoragesource = LevelStorageSource.createDefault(file1.toPath());
            LevelStorageSource.LevelStorageAccess levelstoragesource$levelstorageaccess = levelstoragesource.createAccess(s);
            LevelSummary levelsummary = levelstoragesource$levelstorageaccess.getSummary();

            DataPackConfig datapackconfig = levelstoragesource$levelstorageaccess.getDataPacks();

            PackRepository packrepository = new PackRepository(PackType.SERVER_DATA, new ServerPacksSource(), new FolderRepositorySource(levelstoragesource$levelstorageaccess.getLevelPath(LevelResource.DATAPACK_DIR).toFile(), PackSource.WORLD));
            DataPackConfig datapackconfig1 = MinecraftServer.configurePackRepository(packrepository, DataPackConfig.DEFAULT, false);
            CompletableFuture<ServerResources> completablefuture = ServerResources.loadResources(packrepository.openAllSelected(), registryaccess$registryholder, Commands.CommandSelection.DEDICATED, dedicatedserversettings.getProperties().functionPermissionLevel, Util.backgroundExecutor(), Runnable::run);

            ServerResources serverresources;
            try {
                serverresources = completablefuture.get();
            } catch (Exception exception) {
                LOGGER.warn("Failed to load datapacks, can't proceed with server load. You can either fix your datapacks or reset to vanilla with --safeMode", (Throwable) exception);
                packrepository.close();
                return;
            }

            serverresources.updateGlobals();
            RegistryReadOps<Tag> registryreadops = RegistryReadOps.createAndLoad(NbtOps.INSTANCE, serverresources.getResourceManager(), registryaccess$registryholder);
            dedicatedserversettings.getProperties().getWorldGenSettings(registryaccess$registryholder);
            WorldData worlddata = levelstoragesource$levelstorageaccess.getDataTag(registryreadops, datapackconfig1);
            if (worlddata == null) {
                LevelSettings levelsettings;
                WorldGenSettings worldgensettings;
                DedicatedServerProperties dedicatedserverproperties = dedicatedserversettings.getProperties();
                levelsettings = new LevelSettings(dedicatedserverproperties.levelName, dedicatedserverproperties.gamemode, dedicatedserverproperties.hardcore, dedicatedserverproperties.difficulty, false, new GameRules(), datapackconfig1);
                worldgensettings = dedicatedserverproperties.getWorldGenSettings(registryaccess$registryholder);

                worlddata = new PrimaryLevelData(levelsettings, worldgensettings, Lifecycle.stable());
            }

            levelstoragesource$levelstorageaccess.saveDataTag(registryaccess$registryholder, worlddata);
            WorldData worlddata1 = worlddata;
            SERVER = MinecraftServer.spin((p_129697_) -> {
                DedicatedServer dedicatedserver1 = new DedicatedServer(p_129697_, registryaccess$registryholder,
                    levelstoragesource$levelstorageaccess, packrepository,
                    serverresources, worlddata1, dedicatedserversettings,
                    DataFixers.getDataFixer(), minecraftsessionservice,
                    gameprofilerepository, gameprofilecache, LoggerChunkProgressListener::new);
//                dedicatedserver1.setSingleplayerName("Player");
                dedicatedserver1.setPort(25565);
                dedicatedserver1.setDemo(false);
                // if (!GraphicsEnvironment.isHeadless()) {
                    dedicatedserver1.showGui();
                // }

                return dedicatedserver1;
            });
        } catch (Exception exception1) {
            LOGGER.fatal("Failed to start the minecraft server", (Throwable) exception1);
        }

    }

    static {
        Util.preInitLog4j();
    }
}