---
layout: default
transition: slide-left
---

# 国际化与主题

<style>
.deck-lead { margin-bottom: 0.5rem; font-size: 0.88rem; line-height: 1.4; }
.rail-copy { font-size: 0.78rem; line-height: 1.4; }
.rail-title { font-size: 0.88rem; }
.rail-list { gap: 0.45rem; }
.rail-item { padding-left: 0.7rem; }
</style>

<div class="deck-rule"></div>

<div class="deck-lead">
  国际化与主题切换是完整桌面应用体验的一部分，不只影响外观。系统把语言、主题和重启后状态恢复作为一个整体处理。
</div>

<div class="rail-list">
  <div v-click class="rail-item">
    <div class="rail-index">国际化</div>
    <div class="rail-title"><code>AppLanguage</code> + <code>I18n</code></div>
    <div class="rail-copy"><code>AppLanguage</code> 枚举 <code>English / SimplifiedChinese</code>；图形名、线型名、菜单文案、状态栏提示统一走 <code>I18n</code> 接口。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">主题</div>
    <div class="rail-title"><code>ThemeMode</code> + Fusion 调色板</div>
    <div class="rail-copy"><code>ThemeMode</code> 提供 <code>System / Light / Dark</code> 三档，由 <code>applyApplicationTheme()</code> 统一应用；底层用 Qt Fusion 风格加自定义调色板。</div>
  </div>
  <div v-click class="rail-item">
    <div class="rail-index">状态恢复</div>
    <div class="rail-title">QSettings 持久化</div>
    <div class="rail-copy">语言偏好和主题模式写入 <code>QSettings</code>，<code>TutorialDialog</code> 里的双语 HTML 手册会同步切换，<code>System</code> 模式还监听 <code>QStyleHints::colorSchemeChanged</code>。</div>
  </div>
</div>

<!--
各位老师，这一页我讲国际化和主题的实现细节。AppLanguage 枚举两种语言，I18n 接口统一返回图形名、线型名、菜单文案、状态栏提示。ThemeMode 枚举 System / Light / Dark 三档，applyApplicationTheme 统一应用，底层是 Qt Fusion 风格加自定义 QPalette。System 模式还会监听 QStyleHints::colorSchemeChanged，让调色板跟随操作系统切换。语言偏好和主题模式都写入 QSettings，重启后保留。TutorialDialog 里的双语 HTML 手册会随着语言切换显示对应版本。System 模式额外监听系统外观变化，这是和普通 Light / Dark 切换的关键差异。
-->
