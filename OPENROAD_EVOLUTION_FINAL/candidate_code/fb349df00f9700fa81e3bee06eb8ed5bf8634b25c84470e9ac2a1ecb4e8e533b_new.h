// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.78131557;
  double density_weight = 0.02143088;
  double prefix_weight = 0.07393748;
  double neighborhood_weight = 0.34130596;
  double late_weight = 0.18004310;
  double critical_weight = 0.25702710;
  unsigned budget = 12;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
