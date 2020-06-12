# -*- mode: python ; coding: utf-8 -*-

block_cipher = None


a = Analysis(['snake_game.py'],
             pathex=['/home/marin/snake_python'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)

a.datas += [('snake_icon.png','/home/marin/snake_python/snake_icon.png', "DATA")]
a.datas += [('background_square.png','/home/marin/snake_python/background_square.png', "DATA")]
a.datas += [('snake_square.png','/home/marin/snake_python/snake_square.png', "DATA")]
a.datas += [('red_square.png','/home/marin/snake_python/red_square.png', "DATA")]
a.datas += [('game_over.jpg','/home/marin/snake_python/game_over.jpg', "DATA")]
a.datas += [('victory.png','/home/marin/snake_python/victory.png', "DATA")]
a.datas += [('OpenSans-Bold.ttf','/home/marin/Desktop/test_folder/OpenSans-Bold.ttf', "DATA")]

pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          a.binaries,
          a.zipfiles,
          a.datas,
          [],
          name='snake_game',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          upx_exclude=[],
          runtime_tmpdir=None,
          console=True )
