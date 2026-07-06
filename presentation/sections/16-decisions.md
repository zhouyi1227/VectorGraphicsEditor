---
layout: default
transition: slide-left
---

# 设计决策

<div style="height:2px;width:32px;background:#2d7ff9;margin:0.5rem 0 1.5rem 0;"></div>

<div style="display:grid;grid-template-columns:1fr 1fr;gap:0.75rem;">

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">struct 而非 class</div>
<div style="font-size:0.8rem;color:#666;">ShapeData、SelectionFrame 等纯数据容器用 struct，避免冗余 public 声明</div>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">JSON 而非二进制</div>
<div style="font-size:0.8rem;color:#666;">可读可调试、无字节序、Qt 原生支持、字段扩展不改解析器</div>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">std::function 依赖注入</div>
<div style="font-size:0.8rem;color:#666;">策略与 View 完全解耦，6 个回调替代接口类，测试可注入 mock</div>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">enum class : std::uint8_t</div>
<div style="font-size:0.8rem;color:#666;">强类型作用域 + 指定底层类型节省空间 + 无隐式 int 转换</div>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">静态工厂 + 静态工具</div>
<div style="font-size:0.8rem;color:#666;">FileManager、ShapeFactory 无状态设计，纯函数式接口，调用简洁</div>
</div>

<div v-click style="border:1px solid #e8e8e8;border-radius:6px;padding:0.8rem 1rem;">
<div style="font-weight:600;font-size:0.9rem;">unique_ptr RAII 管理</div>
<div style="font-size:0.8rem;color:#666;">策略对象自动生命周期，异常安全，所有权语义明确</div>
</div>

</div>

<!--
这里总结了6个关键设计决策。纯数据容器用struct减少boilerplate。JSON格式权衡了可读性、调试体验和跨平台兼容性。依赖注入使用std::function而非定义新的接口类，更轻量灵活。所有enum class指定底层类型为uint8_t。静态类避免不必要的对象生命周期管理。unique_ptr保证策略对象的自动释放和异常安全。
-->
