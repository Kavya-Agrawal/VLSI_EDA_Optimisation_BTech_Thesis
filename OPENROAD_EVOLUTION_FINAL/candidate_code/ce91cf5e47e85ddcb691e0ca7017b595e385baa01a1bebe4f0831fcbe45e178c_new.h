// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.32780507;
  double density_weight = 0.18835132;
  double prefix_weight = 0.48616751;
  double neighborhood_weight = 0.12294209;
  double late_weight = 0.18018229;
  double critical_weight = 0.36178267;
  unsigned budget = 40;
  unsigned neighborhood = 1;
  unsigned spatial_mode = 2;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
